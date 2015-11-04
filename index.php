<?php
	header("Content-Type: text/html; charset=utf-8");
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Робот дистанционного присутствия</title>
		<style>
			@import 'css/style.css';
			@import 'css/fonts.css';
		</style>

		<!--<script src='js/jquery-2.1.4.min.js'></script>-->
		<script src='data/keycodes.js'></script>
		<script src='data/uart_mapping.js'></script>
		<script src='js/array.js'></script>
		<script src='js/screenfull.js'></script>
		<script src='js/script.js'></script>

		<!-- Keyboard -->
		<!-- jQuery & jQuery UI + theme (required) -->
		<link href="keyboard/docs/css/jquery-ui.min.css" id="ui-theme" rel="stylesheet">
		<script src="keyboard/docs/js/jquery.min.js"></script>
		<script src="keyboard/docs/js/jquery-ui.min.js"></script>
		<!-- keyboard widget css & script (required) -->
		<link href="keyboard/css/keyboard.css" rel="stylesheet">
		<link href="keyboard/css/keyboard-previewkeyset.css" rel="stylesheet">
		<script src="keyboard/js/jquery.keyboard.js"></script>
		<script src="keyboard/js/jquery.keyboard.extension-extender.js"></script>
		<!-- keyboard extensions (optional) -->
		<script src="keyboard/js/jquery.mousewheel.js"></script>
		<script src="keyboard/js/jquery.keyboard.extension-typing.js"></script>
		<script src="keyboard/js/jquery.keyboard.extension-previewkeyset.js"></script>
		<!-- theme switcher: https://github.com/pontikis/jui_theme_switch/ -->
		<style>
			.switcher_container { padding: 5px; }
			.switcher_list { padding: 2px; }
			.switcher_label { margin-right: 5px; }
			.rtl {
				text-align: right;
			}
		</style>
		<script src="keyboard/docs/js/jquery.jui_theme_switch.min.js"></script>
		<script src='js/keyboard.js'></script>
		<!-- Keyboard end -->

		<script>
			$(function(){

				state = 'work'; // 'test', 'work' - Состояния интерфейса (отладка / работа)
				//keyboard(); //Current problems: activating keyboard when focus is on whole page
				var pressed_keys = []; //Array with keycodes of pressed keyboard keys. (Windows limit is 6 simultaneously)


				$(window).on('resize', fix_size);
				fix_size();

				$('body')/*
					.keypress(function(event){
						keycode = event.which;
						console.info(keycode);
					})*/
					.keydown(function(event){ //Обработка опускания кнопки клавиатуры
						// Getting info about current command
						keycode = event.which;
						console.info(keycode);
						//event.preventDefault();
						process_button(keycode);
						pressed_keys.push(keycode);
						pressed_keys.Unique;
						current_command = get_command_by_code(keycode, uart_mapping);
						commands = keys_to_commands_and_status_keys_display(pressed_keys);

						// Sending all current commands to serial port
						if(state == 'work'){
							command_update_ui(current_command, 'on');
							commands_process(commands);
						}
					})
					.keyup(function(event){ //Обработка поднятия кнопки клавиатуры
						keycode = event.which;
						pressed_keys = array_remove(pressed_keys, keycode);
						current_command = get_command_by_code(keycode, uart_mapping);
						$('#status_keys').text('');
						if(state == 'work')
							command_update_ui(current_command, 'off');
					});
				$('button')
					.mousedown(function(){ //Обработка опускания кнопки мыши
						id = $(this).attr('id');
						command = id.substr(9);
						keycode = get_code_by_command(command, uart_mapping);
						current_command = get_command_by_code(keycode, uart_mapping);
						commands = keys_to_commands_and_status_keys_display([ keycode ]);

						/* Sending all current commands to serial port */
						if(state == 'work'){
							command_update_ui(current_command, 'on');
							commands_process(commands);
						}
					})
					.mouseup(function(){ //Обработка поднятия кнопки мыши
						$('#status_keys').text('');
						if(state == 'work')
							command_update_ui(current_command, 'off');
					})
				$('#screen').dblclick(full_screen_toggle());
			});
		</script>
	</head>
	<body>
		<div id='left'>
			<span id='controls'></span>
		</div>
		<div id='center'>
			<div id='screen'>
				<div id='status_keys'></div>
				<!--<img id='stream' src='http://<? echo $_SERVER['HTTP_HOST']; ?>:8080/?action=stream'></img>-->
			</div>
			<div id="wrap">
				<pre class="prettyprint lang-html">
					<img id="keyboard_icon" class="tooltip-tipsy" title="Click to open the virtual keyboard" src="images/keyboard.png">
					<input id="keyboard_input" type="hidden">
				</pre>
			</div>
			<div id="switcher"></div>
		</div>
		<div id='right'>
			<div id='status_battery'>
				Battery
			</div>
			<div id='controls_move'>
				<button id='controls_forward'>W</button>
				<br>
				<button id='controls_left'>A</button>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<button id='controls_right'>D</button>
				<br>
				<button id='controls_backward'>S</button>
			</div>
			<div id='controls_speed'>
				<button id='controls_sp1'>1</button>
				<button id='controls_sp2'>2</button>
				<button id='controls_sp3'>3</button>
			</div>
			<div id='controls_lights'>
				<button id='controls_lights'>Lights</button>
			</div>
		</div>
</html>