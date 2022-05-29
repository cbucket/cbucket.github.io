// turtle graphic functions for javascript
// Ben Grimer: 20/02/2011

var x0=0;
var y0=0;
var bearing=0;
var x1;
var y1;
var penstate=1;
var PI = Math.PI;
var conv = PI/180;

function gohome() {
  x0=400;
  y0=400;
  bearing=0;
  ctx.moveTo(x0,y0);
}

function cs() { canvas.width = canvas.width; gohome(); }

function pu() {
  penstate=0;
}

function pd() {
  penstate=1;
  ctx.moveTo(x0, y0);
}

function commit() { ctx.stroke(); }
function render() { ctx.stroke(); }

function pencolor(_color) {

	ctx.stroke();
	ctx.strokeStyle = _color;
	ctx.beginPath();
	ctx.moveTo(x0, y0);
}

function west(_dist)
{
  lt(90); fd(_dist); rt(90);
}

function east(_dist)
{
  west(-_dist);
}

function fd(_dist) {
  y1=y0 - _dist*Math.cos(bearing*conv);
  x1=x0 + _dist*Math.sin(bearing*conv);
  if (penstate==1) {
    ctx.lineTo(x1, y1);
  } else {
    ctx.moveTo(x1, y1);
  }
  x0=x1;
  y0=y1;
}

function bk(_dist) {
  fd(-_dist);
}

function rt(_angle) {
  bearing = bearing + _angle;
}

function lt(_angle) {
  rt(-_angle);
}

function arc(){
  var radians = (Math.PI/180)
  var centerX = 288;
	var centerY = 160;
	var radius= 75;
	var startingAngle = radians*20;
	var endingAngle = radians*400;
	var counterclockwise = false;
 
	ctx.arc(centerX,centerY, radius, startingAngle, 
		endingAngle,counterclockwise);
   
}

