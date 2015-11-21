//Parses object with keycodes and gets key symbols
function get_symbol_by_code(code, keycodes){
	for(var key in keycodes){
		if(keycodes[key] == code)
			var symbol = key;
	}
	return symbol;
}

function process_button(code){
	if(code == 70)
		full_screen_toggle();
}

//Parses object with keycodes and gets commands
function get_command_by_code(code, command_mapping){
	for(var command in command_mapping){
		for(var key in command_mapping[command])
			if(command_mapping[command][key] == code)
				var c = command;
	}
	return c;
}

function get_code_by_command(command, command_mapping){
	found = false;
	for(c in command_mapping)
		if(c == command)
			found = command_mapping[c][0];
	return found;
}

function commands_process(commands){
	commands_to_serial_port(commands);
}

function command_update_ui(command, action){
	if(action == 'on')
		$('#controls_' + command).css('background', 'rgba(128,255,0,0.5)');
	else if(action == 'off'){
		$('#controls_' + command).css('background', 'transparent');
		$('#controls_' + command)
			.hover(function(){ $(this).css('background', 'rgba(255, 128, 0, 0.5)'); })
			.mouseleave(function(){ $(this).css('background', 'transparent'); });
	}
}

function commands_to_serial_port(commands){
	$.ajax('serial_connector.php', { 'data': {'actions': commands} });
}

function keys_to_commands_and_status_keys_display(pressed_keys){
	var commands = []; console.info(pressed_keys);
	var keycodes_text = '', commands_text = '';
	for(var i=0; i<pressed_keys.length; i++) {
		keycode = pressed_keys[i];
		keycodes_text += '<font color=white>' + get_symbol_by_code(keycode, keycodes) + '</font> ';
		command = get_command_by_code(keycode, uart_mapping);
		commands_text += '<font color=white>' + command + '</font> ';
		commands.push(command);
	}
	status_keys_display([keycodes_text, commands_text]);
	return commands;
}

function status_keys_display(data){
	if(Array.isArray(data))
		$('#status_keys').html('Pressed keys: ' + data[0] + '<br>' + 'Called commands: ' + data[1]);
	else
		$('#status_keys').html('');
}


function full_screen_toggle(){
	var target = $('#screen')[0]; // Get DOM element from jQuery collection
	if(screenfull.enabled)
		screenfull.toggle(target);
}

function fix_size() {
	var images = $('#stream');
	images.each(setsize);

	function setsize() {
		var img = $(this),
			img_dom = img.get(0),
			container = img.parents('#screen');
		if (img_dom.complete) {
			resize();
		} else img.one('load', resize);

		function resize() {
			if ((container.width() / container.height()) < (img_dom.width / img_dom.height)) {
				img.width('100%');
				img.height('100%');
				return;
			}
			img.height('100%');
			img.width('100%');
		}
	}
}

function absorbEvent_(event){
	var e = event || window.event;
	e.preventDefault && e.preventDefault();
	e.stopPropagation && e.stopPropagation();
	e.cancelBubble = true;
	e.returnValue = false;
	return false;
}

function preventLongPressMenu(node){
	node.ontouchstart = absorbEvent_;
	node.ontouchmove = absorbEvent_;
	node.ontouchend = absorbEvent_;
	node.ontouchcancel = absorbEvent_;
}