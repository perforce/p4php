<?php

require_once 'helper.inc';

if (!file_exists(DEPOT_ROOT))
    mkdir(DEPOT_ROOT);

if (!file_exists(CLIENT_ONE_ROOT))
    mkdir(CLIENT_ONE_ROOT);

if (!file_exists(CLIENT_TWO_ROOT))
    mkdir(CLIENT_TWO_ROOT);

$p4d = whichP4d();

// die early (and loudly) if no p4d can be found.
if ($p4d === false) {
	die('Cannot locate p4d binary. Aborting!');
}

// create instance and connect.
$p4 = new P4();
$p4->port = "rsh:$p4d -r " . DEPOT_ROOT . " -i";
$p4->user = "tester";
$p4->tagged = true;
$p4->connect();

// On p4d 2026.1+ ("Secure By Default") password authentication is enforced from
// the very first connection; the only operation allowed pre-auth is setting the
// initial password. Set it first (no old password on a fresh server), then log
// in so a ticket is cached for the rest of the test.
$p4->run_password('', SUPER_PASSWORD);
$p4->password = SUPER_PASSWORD;
$p4->run_login(SUPER_PASSWORD);

// create user (now authenticated).
$user = $p4->fetch_user();
$user['Name'] = 'tester';
$p4->save_user($user);

// create clients
$p4->client = CLIENT_ONE_NAME;
$clientOne = $p4->fetch_client();
$clientOne['Root'] = CLIENT_ONE_ROOT;
$p4->save_client($clientOne);

$p4->client = CLIENT_TWO_NAME;
$clientTwo = $p4->fetch_client();
$clientTwo['Root'] = CLIENT_TWO_ROOT;
$p4->save_client($clientTwo);


