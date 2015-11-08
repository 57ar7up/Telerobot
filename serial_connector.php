<?php
	require 'config.php';
	//Git Submodules
	require 'php_serial.class.php'; //'Submodules/PHP-Serial/src/PhpSerial.php';
	//require 'Submodules/virtualjoystick.js/virtualjoystick.js';

	$test_mode = FALSE;
	$uart = '/dev/ttyATH0'; //'/../dev/ttyATH0';
	$baud_rate = 57600;

	if($test_mode)
		serial_test();

	$actions = $_GET['actions'];
	if(isset($actions)){
		print_r($actions);
		$serial = new phpSerial();
		$serial->deviceSet($uart);
		$serial->confBaudRate($baud_rate);
		$serial->deviceOpen();

		//$serial->sendMessage('YE'); //Control string

		$serial->sendMessage($actions[0]);

		$serial->deviceClose();
	}

	function serial_test(){
		global $uart, $baud_rate;
		echo "Test mode";
		$serial = new phpSerial();
		$serial->deviceSet($uart);
		$serial->confBaudRate($baud_rate);
		$serial->deviceOpen();
		$serial->sendMessage(1);
		$serial->deviceClose();
		exit;
	}
/*
serial_init($uart);

while(true){
	$msg = readline('> ');//stream_get_line(STDIN, 1, PHP_EOL); // Readline not available on Win, Iduino
	if($msg == 'exit'){
		break;
	}

	echo "* sending... ";
	if(sendMessage($fp, $msg)){
		echo "OK\n\n";
	}
	else {
		echo "FAILED!!!\n\n";
	}

	echo readMessage($fp)."\n";
}

serial_close();
*/

?>