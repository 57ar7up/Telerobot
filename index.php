<?php

	header("Content-Type: text/html; charset=utf-8");

	define('USER', 'admin');
    define('PASSWORD', '123');
    if (!isset($_SERVER['PHP_AUTH_USER']) || !isset($_SERVER['PHP_AUTH_PW'])){
        header('WWW-Authenticate: Basic realm="My Realm"');
        header('HTTP/1.0 401 Unauthorized');
        die('You choosed cancel');
    } elseif (isset($_SERVER['PHP_AUTH_USER']) && $_SERVER['PHP_AUTH_USER'] == USER && isset($_SERVER['PHP_AUTH_PW']) && $_SERVER['PHP_AUTH_PW'] == PASSWORD) {
       	$user = $_SERVER['PHP_AUTH_USER'];
        $password = $_SERVER['PHP_AUTH_PW'];
    } else {
        header('HTTP/1.0 400 Bad Request');
        die('No access');
    }

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
		<script src="keyboard/docs/js/jquery.min.js"></script>
		<script src='js/array.js'></script>
		<script src='js/screenfull.js'></script>
		<script src='js/script.js'></script>

		<!-- Keyboard -->
		<!-- jQuery UI + theme (required) -->
		<!--<link href="keyboard/docs/css/jquery-ui.min.css" id="ui-theme" rel="stylesheet">
		<script src="keyboard/docs/js/jquery-ui.min.js"></script>-->
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
		<!--<script src="keyboard/docs/js/jquery.jui_theme_switch.min.js"></script>-->
		<script src='js/keyboard.js'></script>
		<!-- Keyboard end -->

		<script>
			$(function(){

				state = 'work'; // 'test', 'work' - Состояния интерфейса (отладка / работа)
				motors_stop_symbol = ' ';

				//keyboard(); //Current problems: activating keyboard when focus is on whole page
				var pressed_keys = []; //Array with keycodes of pressed keyboard keys. (Windows limit is 6 simultaneously)

				$(window).on('resize', fix_size);
				fix_size();
				last_keycode = null;

				$('body')
					.keydown(function(event){ //Обработка опускания кнопки клавиатуры
						keycode = event.which;
						if(keycode != last_keycode){
							last_keycode = keycode;
							console.info(keycode);
							//event.preventDefault();
							process_button(keycode);
							pressed_keys.push(keycode);
							pressed_keys.Unique;
							current_command = get_command_by_code(keycode, uart_mapping);
							commands = keys_to_commands_and_status_keys_display(pressed_keys);

							if(state == 'work'){	//Если рабочий режим, посылаем в серийный интерфейс
								command_update_ui(current_command, 'on');
								commands_process(commands);
							}
						}
					})
					.keyup(function(event){ //Обработка поднятия кнопки клавиатуры
						last_keycode = null;
						keycode = event.which;
						pressed_keys = array_remove(pressed_keys, keycode);
						current_command = get_command_by_code(keycode, uart_mapping);
						if(state == 'work'){
							command_update_ui(current_command, 'off');
							commands_process([motors_stop_symbol]);
						}
					});
				$('button')	//Обработка нажания на экранные кнопки
					.mousedown(function(){ //Обработка опускания кнопки мыши
						id = $(this).attr('id');
						command = id.substr(9);
						keycode = get_code_by_command(command, uart_mapping);
						if(keycode != last_keycode){
							last_keycode = keycode;
							current_command = get_command_by_code(keycode, uart_mapping);
							commands = keys_to_commands_and_status_keys_display([ keycode ]);

							if(state == 'work'){	//Если рабочий режим, посылаем в серийный интерфейс
								command_update_ui(current_command, 'on');
								commands_process(commands);
							}
						}
					})
					.mouseup(function(){ //Обработка поднятия кнопки мыши
						last_keycode = null;
						if(state == 'work'){
							command_update_ui(current_command, 'off');
							commands_process([motors_stop_symbol]);
						}
					})
				$('#screen').dblclick(full_screen_toggle());
			});
		</script>
	</head>
	<body>
		<div id='left'>
			<div id='controls_move'>
				<button id='controls_w' class='big'>↑</button>
				<div class='space'></div>
				<button id='controls_s' class='big'>↓</button>
			</div>
		</div>
		<div id='center'>
			<div id='screen'>
				<div id='auth'>
					Hello, <b><?php echo $user; ?></b>
					<span style='display:none'><?php echo $password; ?></span>
				</div>
				<div id='status_keys'></div>
				<img id='stream' src='http://<?php echo $_SERVER['HTTP_HOST']; ?>:8080/?action=stream'></img>
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
				<button id='controls_a' class='big'>←</button>
				&nbsp;&nbsp;&nbsp;
				<button id='controls_d' class='big'>→</button>
			</div>
			<div id='controls_other'>
				<span id='controls_speed'>
					<button id='controls_sp1'>1</button>
					<button id='controls_sp2'>2</button>
					<button id='controls_sp3'>3</button>
				</span>
				<span id='controls_lights'>
					<button id='controls_lights'>Lights</button>
				</span>
			</div>
		</div>
</html>