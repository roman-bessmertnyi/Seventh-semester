var x, y, z;
x=6;
y=15;
z=4;

window.onload = function() {
    calculate();
	return;
  };

function calculate() {
    document.getElementById("x").innerHTML = x; 
	document.getElementById("y").innerHTML = y; 
	document.getElementById("z").innerHTML = z; 
	x += y - x++ * z;
	document.getElementById("stat1").innerHTML = x; 
	z = -- x - y * 5;
	document.getElementById("stat2").innerHTML = z; 
	y /= x + 5 % z;
	document.getElementById("stat3").innerHTML = y; 
	z = x++ + y * 5;
	document.getElementById("stat4").innerHTML = z; 
	x = y - x++ * z;
	document.getElementById("stat5").innerHTML = x; 
	return;
}

function mean(a, b, c) {
    return (a+b+c)/3;
}

function cylinderVolume(r, h) {
	var V;
	V = Math.PI * r*r * h;
    return V;
}

function cylinderSurface(r, h) {
	var S;
	var pi = Math.PI;
	var sum = (r + h);
	S = 2 * pi * r * sum;
    return S;
}

function calculateCylinder() {
	var r = parseInt(document.getElementById("r").value, 10);
    var h = parseInt(document.getElementById("h").value, 10);
    document.getElementById("V").innerHTML = cylinderVolume(r,h); 
	document.getElementById("S").innerHTML = cylinderSurface(r,h); 
}