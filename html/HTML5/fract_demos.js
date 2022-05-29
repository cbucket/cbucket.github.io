// fract_demos.js
// 20/02/2011
//------------------------------------------

function koch_demo()
{
  cs(); pu();fd(200); rt(90); bk(200) ;pd();

  pencolor("gold");
	koch(400, 20);
  rt(120);
	koch(400, 20);
  rt(120);
	koch(400, 20);
  rt(120);

//  rt(90); fd(50); rt(90); fd(400); rt(90); fd(50); rt(90);

  ctx.fillStyle = "gold";
  ctx.fill();

  commit();
}

//------------------------------------------
function snowsweep_demo2 ()
{
  cs(); pu();bk(150); rt(90); bk(250) ;pd();
  pencolor("red");
  snowsweepX_forward(600, 2, 1);

  rt(90); fd(200); rt(90); fd(600); rt(90); fd(200); rt(90);
//  ctx.fillStyle = "blue"; ctx.fill();
  commit();

}

//------------------------------------------
function snowsweep_demo ()
{
  cs(); pu();bk(150); rt(90); bk(250) ;pd();
  pencolor("purple");
  snowsweep_forward(600, 5, 1);

  rt(90); fd(200); rt(90); fd(600); rt(90); fd(200); rt(90);
  ctx.fillStyle = "green"; ctx.fill();
  commit();

}

//------------------------------------------
function monkey_demo(_order)
{
//alert("order is " + _order);
  if (_order < 5) {
    cs(); pu(); bk(150); rt(90); bk(300) ;pd();
    pencolor("gold");
    monkeyX_forward(600, _order, 1);

    rt(90); fd(200); rt(90); fd(600); rt(90); fd(200); rt(90);
    ctx.fillStyle = "purple"; ctx.fill();
    commit();
  } else alert("order too high! May crash browser.");
}

//------------------------------------------

function squaresweep_demo()
{
  cs(); pu();bk(200); rt(90); bk(200) ;pd();
  pencolor("green");
  square_sweep(500, 10, 85, 1);
  commit();
}

//------------------------------------------

function template_demo(name, _order) {

  var _size = 800;
  _order = parseInt(_order);

  gohome(); pu(); rt(90); bk(350) ;pd();

  if (name == "koch") {
    pencolor("black");
    koch(_size, _order);
  } else if (name == "cesaro") {
    pencolor("red");
    cesaro(_size, _order, 30);
  } else if (name == "concrete") {
    pencolor("blue");
    cesaro(_size, _order, 40);
  } else if (name == "concrete2") {
    pencolor("magenta");
    cesaro(_size, _order, 44);
  } else if (name == "snowsweep") {
    pencolor("orange");
    pu(); lt(90); bk(100); rt(90) ;pd();
    snowsweepX_forward(600, _order, 1);
  } else if (name == "koch4") {
    pu(); lt(90); bk(300); rt(90) ;pd();
    pencolor("black");
    koch(_size, _order);
    pu(); bk(_size); lt(90); fd(50); rt(90); pd();
//alert("order+1 >" + (_order+1) + "<");
    koch(_size, _order+1);
    pu(); bk(_size); lt(90); fd(100); rt(90); pd();
//alert("order+2 >" + (_order+2) + "<");
    koch(_size, _order+2);
    pu(); bk(_size); lt(90); fd(150); rt(90); pd();
    koch(_size, _order+3);
  } else if (name == "monkey") {
    pencolor("green");
    pu(); lt(90); bk(100); rt(90) ;pd();
    monkeyX_forward(600, _order, 1);
  } else alert("invalid template demo");

  commit();

}

//------------------------------------------

function snowflake(_order) {

  cs(); pu();fd(200); rt(90); bk(200) ;pd();

  pencolor("green");
	koch(400, _order);
	rt(120);

    pencolor("blue");
	koch(400, _order);
	rt(120);

	pencolor("red");
	koch(400, _order);
	rt(120);
  commit();

}

//------------------------------------------

function twindragon() {

	pencolor("red");
	dragon(200, 15, 45);
	rt(180);
	pencolor("blue");
	dragon(200, 15, 45);
  commit();

}

//------------------------------------------

function twincesaro(_size, _order) {

  _order = parseInt(_order);
  cs(); pu();fd(100); rt(90); bk(200) ;pd();
	pencolor("red");
	cesaro(_size, _order, 40);
	rt(180)
	pencolor("gold");
	cesaro(_size, eval(_order+1), 40);
  commit();
}

function star_demo()
{
  cs(); pu();bk(100); rt(90); bk(200) ;pd();
  star(100, 15);
  ctx.fillStyle = "gold";
  ctx.fill();

  render();
}

function polygonDemo() {
  cs(); pu();bk(300);lt(90); bk(100) ;pd();
  for (i=3; i<21; i++) {
    polygon(100, i);
  }
  render();
}

function joeCity() {
  rt(90);pu();bk(390);pd();
  city(700, 5);
}

function joeFractal() {
  pu(); bk(200); rt(90); fd(200); lt(90); pd();
  joe(200, 3);
}