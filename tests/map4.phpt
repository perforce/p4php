--TEST--
P4_Map - Test P4_Map multiple keys, key types, return values
--ARGS--
-c tests/php.ini
--FILE--
<?php
// Suppress warning arising from type hinting, as we're deliberately passing
// wrong types to includes()
error_reporting(E_ALL^E_WARNING);
$LIMIT = 1000;
$map = new P4_Map(array(
    "//depot/main/...   //client/...",
    "-//depot/main/something/... -//client/something/..."
));

// Control test - true
$ep = "//depot/main/...";
var_dump($map->includes($ep));

// Create a resource and use that for test, should be NULL as it's not a string
$fp = tmpfile();
var_dump($map->includes($fp));

// Close resource, creating type unknown. includes() should return NULL.
fclose($fp);
var_dump($map->includes($fp));

// Number, not a string.  Should return false, as numbers can be parsed as strings.
$gp = 12345;
var_dump($map->includes($gp));

// Set references to map object, try using object as key, should return NULL.
$hp = $map;
var_dump($map->includes($hp));

// Use NULL/Empty as a key, not a string, but it parses as one and should return false.
$ip = NULL;
var_dump($map->includes($ip ?? ''));

--EXPECTF--
bool(true)
NULL
NULL
bool(false)
NULL
bool(false)
