--TEST--
 Evil twin test
--ARGS--
 -c tests/php.ini
--SKIPIF--
 <?php
 include_once 'helper.inc';
 requireP4d();
 if( !str_contains( P4::identify(), "Parallel sync threading built-in" ) ) {
   die( "P4API doesn't have built-in parallel sync support!" );
 }
 ?>
--FILE--
 <?php
 include 'connect.inc';

 date_default_timezone_set("America/Vancouver");

$p4->client = CLIENT_ONE_NAME;
$client = $p4->fetch_client();
$root = $client["Root"];
$dirA = CLIENT_ONE_ROOT . DIRECTORY_SEPARATOR . "A";
$dirB = CLIENT_ONE_ROOT . DIRECTORY_SEPARATOR . "B";

if (!file_exists($dirA))
    mkdir($dirA);

$fileA = $dirA . DIRECTORY_SEPARATOR . "FileA.txt";
$fileA1 = $dirA . DIRECTORY_SEPARATOR . "FileA1.txt";
$fp1 = fopen($fileA, 'w');
fwrite($fp1, "original A");
fclose($fp1);

$p4->run_add($root . "/...");
$change = $p4->fetch_change();
$change['Description'] = "Testing run_submit 1 arg";
$results = $p4->run_submit($change);

$branch_spec = $p4->run("branch", "-o", "evil-twin-test");
$branch_spec[0]["View"][0] = "//depot/A/... //depot/B/...";

$p4->input = $branch_spec[0];
$p4->run("branch", "-i");
$p4->run("integ", "-b", "evil-twin-test");
$p4->run("submit", "-d", "integrating");

$p4->run("edit", "$fileA");
$p4->run("move", "-f", "$fileA", "$fileA1");
$p4->run("submit", "-d", "moving");

$fp2 = fopen($fileA, 'w');
fwrite($fp2, "Re-added A");
fclose($fp2);

$p4->run("add", $fileA);
$p4->run("submit", "-d", "re-adding");

try {
  $p4->run("merge", "-b", "evil-twin-test");
  $p4->run("submit", "-d", "integrating");
} catch (Exception $e) {

  echo 'Caught exception: ', $e->getMessage(), "\n";

}

 ?>
--CLEAN--
 <?php
 require_once('teardown.inc');
 ?>
--EXPECTF--
Caught exception: [P4.run()] Errors during command execution( "p4 submit -d integrating" )

	[Error]: Merges still pending -- use 'resolve' to merge files.
Submit failed -- fix problems above then use 'p4 submit -c %d'.