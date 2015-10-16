
//Get keys from array which are true
function array_keys_true(array){
	var result = [];
	for(element in array)
		if(element)
			result.push(array[element]);
	return result;
}

/*Remove value from array
	Example:
	var array = ['one', 'two', 'three'];
	array_remove(array, 'three');
	Result:
	array = ['one', 'two'];
*/
function array_remove(arr) {
	var what, a = arguments, L = a.length, ax;
	while (L > 1 && arr.length) {
		what = a[--L];
		while ((ax= arr.indexOf(what)) !== -1) {
			arr.splice(ax, 1);
		}
	}
	return arr;
}

Array.prototype.Unique = function(){
	var u = {}, a = [];
	for(var i = 0, l = this.length; i < l; ++i){
		if(u.hasOwnProperty(this[i]))
			continue;
		a.push(this[i]);
		u[this[i]] = 1;
	}
	return a;
}