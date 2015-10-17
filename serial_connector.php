<?php
	require 'config.php';
	//Git Submodules
	require 'php_serial_ssty_fixed.class.php'; //'Submodules/PHP-Serial/src/PhpSerial.php';
	//require 'Submodules/virtualjoystick.js/virtualjoystick.js';
	require 'php_serial_header.php';

	$test_mode = TRUE;

	if($test_mode)
		serial_test();

	$actions = $_GET['actions'];
	if(isset($actions)){
		$device = '/dev/ttyATH0'; //'/../dev/ttyATH0';
		$baud_rate = 115200;

		$serial = new phpSerial();
		$serial->deviceSet($device);
		$serial->confBaudRate($baud_rate);
		$serial->deviceOpen();

		foreach($actions as $action){
			$serial->sendMessage(0xff);
			$act = str_split($action);
			foreach($act as $char)
				$serial->sendMessage($char);
		}

		$serial->deviceClose();
	}

	function serial_test(){
		echo "Test mode";
		$serial = new phpSerial();
		$serial->deviceSet('/dev/ttyATH0');
		$serial->confBaudRate(115200);
		$serial->deviceOpen();
		$serial->sendMessage(1);
		$serial->deviceClose();
		exit;
	}
/*
serial_init($device);

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