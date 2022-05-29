// fractal functions
// requires 'turtle.js' to work
// Ben Grimer: 20/02/2011

// this function implements a gosper curve or flowsnake
// Ben Grimer: 22/02/2011
// from: http://en.wikipedia.org/wiki/Gosper_curve
// logo version translated to javascript turtle graphics implementation
function rg(siz,ord) {
  var root7 = Math.sqrt(7);
  var ns = siz/root7;  // ns = new size
  var no = ord-1;

  if (ord < 1) {
    fd(ns);rt(60);fd(ns);rt(120);fd(ns);lt(60);fd(ns);lt(120);fd(ns);fd(ns);lt(60);fd(ns);rt(60);
  } else {
    rg(ns,no);rt(60);gl(ns,no);rt(120);gl(ns,no);lt(60);rg(ns,no);lt(120);rg(ns,no);rg(ns,no);lt(60);gl(ns,no);rt(60);
  }
}

// this is the twin of rg() above
function gl(siz,ord) {
  var root7 = Math.sqrt(7);
  var ns = siz/root7;  // ns = new size
  var no = ord-1;

  if (ord < 1) {
    lt(60);fd(ns);rt(60);fd(ns);fd(ns);rt(120);fd(ns);rt(60);fd(ns);lt(120);fd(ns);lt(60);fd(ns);
  } else {
    lt(60);rg(ns,no);rt(60);gl(ns,no);gl(ns,no);rt(120);gl(ns,no);rt(60);rg(ns,no);lt(120);rg(ns,no);lt(60);gl(ns,no);
  }
}


//------------------------------------------
// Mandelbrot, page: 68
function snowsweep_forward(_size, _order, _dir)
{
	var twoCos30 = 2*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  lt(60 * _dir);
	  snowsweep_forward(_size/3, _order-1, -_dir);
	  snowsweep_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweep_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweep_reverse(_size/3, _order-1, _dir);
    rt(90 * _dir);
    snowsweep_reverse(twoCos30*(_size/3), _order-1, -_dir)
	  lt(150 * _dir);
	  snowsweep_forward(_size/3, _order-1, -_dir);
	  snowsweep_reverse(_size/3, _order-1, _dir);
	}
}

//------------------------------------------
// Mandelbrot, page: 68
function snowsweep_reverse(_size, _order, _dir)
{
	var twoCos30 = 2*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  snowsweep_forward(_size/3, _order-1, _dir);
	  snowsweep_reverse(_size/3, _order-1, -_dir);
	  lt(150 * _dir);
    snowsweep_forward(twoCos30*(_size/3), _order-1, -_dir)
    rt(90 * _dir);
	  snowsweep_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweep_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweep_forward(_size/3, _order-1, _dir);
	  snowsweep_reverse(_size/3, _order-1, -_dir);
	  lt(60 * _dir);
	}
}

//------------------------------------------
// Mandelbrot, page: 68
function snowsweepX_forward(_size, _order, _dir)
{
	var twoCos30 = 2*Math.cos(30*conv);

	if (_order<1 || _size<40) {
	  fd(_size);
	} else {
	  lt(60 * _dir);
	  snowsweepX_forward(_size/3, _order-1, -_dir);
	  snowsweepX_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweepX_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweepX_reverse(_size/3, _order-1, _dir);
    rt(90 * _dir);
    snowsweepX_reverse(twoCos30*(_size/3), _order-1, -_dir);
	  lt(150 * _dir);
	  snowsweepX_forward(_size/3, _order-1, -_dir);
	  snowsweepX_reverse(_size/3, _order-1, _dir);
	}
}

//------------------------------------------
// Mandelbrot, page: 68
function snowsweepX_reverse(_size, _order, _dir)
{
	var twoCos30 = 2*Math.cos(30*conv);

	if (_order<1 || _size<40) {
	  fd(_size);
	} else {
	  snowsweepX_forward(_size/3, _order-1, _dir);
	  snowsweepX_reverse(_size/3, _order-1, -_dir);
	  lt(150 * _dir);
    snowsweepX_forward(twoCos30*(_size/3), _order-1, -_dir);
    rt(90 * _dir);
	  snowsweepX_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweepX_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  snowsweepX_forward(_size/3, _order-1, _dir);
	  snowsweepX_reverse(_size/3, _order-1, -_dir);
	  lt(60 * _dir);
	}
}

//------------------------------------------
function monkey_forward(_size, _order, _dir)
{
	var sixCos30 = 6*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  lt(60 * _dir);
	  monkey_forward(_size/3, _order-1, -_dir);
    monkey_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  monkey_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
    monkey_reverse(_size/3, _order-1, _dir);
    rt(150 * _dir);
    monkey_reverse(_size/sixCos30, _order-1, _dir);
	  monkey_forward(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkey_reverse(_size/sixCos30, _order-1, _dir);
	  lt(60 * _dir);
    monkey_reverse(_size/sixCos30, _order-1, -_dir);
	  monkey_forward(_size/sixCos30, _order-1, _dir);
    lt(90 * _dir);
    monkey_reverse(_size/3, _order-1, -_dir);
	  monkey_forward(_size/3, _order-1, _dir);
	}
}

//------------------------------------------
function monkey_reverse(_size, _order, _dir)
{
	var sixCos30 = 6*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  monkey_reverse(_size/3, _order-1, _dir);
    monkey_forward(_size/3, _order-1, -_dir);
    lt(90 * _dir);
	  monkey_reverse(_size/sixCos30, _order-1, _dir);
    monkey_forward(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkey_forward(_size/sixCos30, _order-1, _dir);
	  lt(60 * _dir);
    monkey_reverse(_size/sixCos30, _order-1, -_dir);
	  monkey_forward(_size/sixCos30, _order-1, _dir);
    rt(150 * _dir);
    monkey_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  monkey_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
    monkey_forward(_size/3, _order-1, _dir);
	  monkey_reverse(_size/3, _order-1, -_dir);
	  lt(60 * _dir);
	}
}

//------------------------------------------
function monkeyX_forward(_size, _order, _dir)
{
	var sixCos30 = 6*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  lt(60 * _dir);
	  monkeyX_forward(_size/3, _order-1, -_dir);
    monkeyX_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  monkeyX_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
    monkeyX_reverse(_size/3, _order-1, _dir);
    rt(150 * _dir);
    monkeyX_reverse(_size/sixCos30, _order-1, _dir);
	  monkeyX_forward(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkeyX_reverse(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkeyX_reverse(_size/sixCos30, _order-1, -_dir);
	  monkeyX_forward(_size/sixCos30, _order-1, _dir);
    lt(90 * _dir);
    monkeyX_reverse(_size/3, _order-1, -_dir);
	  monkeyX_forward(_size/3, _order-1, _dir);
	}
}

//------------------------------------------
function monkeyX_reverse(_size, _order, _dir)
{
	var sixCos30 = 6*Math.cos(30*conv);

	if (_order<1) {
	  fd(_size);
	} else {
	  monkeyX_reverse(_size/3, _order-1, _dir);
    monkeyX_forward(_size/3, _order-1, -_dir);
    lt(90 * _dir);
	  monkeyX_reverse(_size/sixCos30, _order-1, _dir);
    monkeyX_forward(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkeyX_forward(_size/sixCos30, _order-1, -_dir);
	  lt(60 * _dir);
    monkeyX_reverse(_size/sixCos30, _order-1, -_dir);
	  monkeyX_forward(_size/sixCos30, _order-1, _dir);
    rt(150 * _dir);
    monkeyX_forward(_size/3, _order-1, _dir);
	  rt(60 * _dir);
	  monkeyX_reverse(_size/3, _order-1, _dir);
	  rt(60 * _dir);
    monkeyX_forward(_size/3, _order-1, _dir);
	  monkeyX_reverse(_size/3, _order-1, -_dir);
	  lt(60 * _dir);
	}
}

//------------------------------------------
// sierpinski arrowhead (gasket)
function serpinski(_size, _order, _angle)
{
	if (_order<1) {
	  fd(_size);
	} else {
	  lt(_angle);
	  serpinski(_size/2, _order-1, -_angle);
	  rt(_angle);
	  serpinski(_size/2, _order-1, _angle);
	  rt(_angle);
	  serpinski(_size/2, _order-1, -_angle);
	  lt(_angle);
	}
}

//------------------------------------------
function dragon(_size, _order, _angle)
{
	if (_order<1) {
	  fd(_size);
	} else {
	  lt(_angle);
	  dragon(_size/(2*Math.cos(_angle*conv)), _order-1, -Math.abs(_angle));
	  rt(_angle*2);
	  dragon(_size/(2*Math.cos(_angle*conv)), _order-1, Math.abs(_angle));
	  lt(_angle);
	}
}

//------------------------------------------
// this is a variation on the dragon curve but experimenting with colours

function dragon2(_size, _order, _angle, _color)
{
	if (_order<1) {
	  pencolor(_color);
	  fd(_size);
	} else {
	  lt(_angle);
	  dragon2(_size/(2*Math.cos(_angle*conv)), _order-1, -Math.abs(_angle), "red");
	  rt(_angle*2);
	  dragon2(_size/(2*Math.cos(_angle*conv)), _order-1, Math.abs(_angle), "green");
	  lt(_angle);
	}
}


//------------------------------------------
function cesaro2(_size, _order, _angle) {

	if (_order<1) {
	  fd(_size);
	} else {
	  lt(_angle);
	  cesaro(_size/(2*Math.cos(_angle*conv)), _order-1, Math.abs(_angle));
	  rt(_angle*2);
	  cesaro(_size/(2*Math.cos(_angle*conv)), _order-1, -Math.abs(_angle));
	  lt(_angle);
	}
}

//------------------------------------------
function cesaro(_size, _order, _angle) {

	if (_order<1) {
	  fd(_size);
	} else {
	  lt(_angle);
	  cesaro(_size/(2*Math.cos(_angle*conv)), _order-1, -_angle);
	  rt(_angle*2);
	  cesaro(_size/(2*Math.cos(_angle*conv)), _order-1, -_angle);
	  lt(_angle);
	}
}


//------------------------------------------
function koch(_size, _order) {

  if (_order < 1 || _size<1) {
    fd(_size);
  } else {
    koch(_size/3, _order-1);
	lt(60);
    koch(_size/3, _order-1);
    rt(120);
    koch(_size/3, _order-1);
	lt(60);
    koch(_size/3, _order-1);
  }

}
//------------------------------------------
function joe(_size, _order)
{
	if (_order<1 || _size<1) {
	  fd(_size);
	} else {
	  fd(_size/6);
	  lt(90);
	  joe(_size/3, _order-1);
	  joe(_size/4, _order-1);
	  rt(90);
	  joe(_size/3, _order-1);
	  rt(90);
	  joe(_size/4, _order-1);
	  joe(_size/3, _order-1);
	  lt(90);
	  joe(_size/6, _order-1);
	  joe(_size/3, _order-1);
	}
}
//------------------------------------------
function pnoc(_size, _order)
{
	if (_order<1 || _size<1) {
	  fd(_size);
	} else {
	  pnoc(_size/4, _order-1);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  rt(90);
	  pnoc(_size/4, _order-1);
	  pnoc(_size/4, _order-1);
	  rt(90);
	  pnoc(_size/4, _order-1);
	  rt(90);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  pnoc(_size/4, _order-1);
	  lt(90);
	  pnoc(_size/4, _order-1);
	  rt(90);
	  pnoc(_size/4, _order-1);
	  pnoc(_size/4, _order-1);
	  lt(90);
	}
}

//------------------------------------------
function city(_size, _order)
{
  var rad = 1; // Math.floor(Math.random()*2);
  var s2 = _size/3;
	if (_order<1 || _size<1) {
	  fd(_size);
	} else {
	  city(_size/3, _order-1);
	  lt(90);
	  fd(s2*rad);
	  rt(90);
	  city(_size/3, _order-1);
	  rt(90);
	  fd(s2*rad);
	  lt(90);
	  city(_size/3, _order-1);
	}
}
//------------------------------------------
function koch_pyramid(_size, _order) {

  if (_order < 1 || _size < 1) {
    fd(_size);
  } else {
    koch_pyramid(_size/3, _order-1);
	lt(90);
    koch_pyramid(_size/3, _order-1);
	rt(90);
    koch_pyramid(_size/3, _order-1);
	rt(90);
    koch_pyramid(_size/3, _order-1);
	lt(90);
    koch_pyramid(_size/3, _order-1);
  }
}


//------------------------------------------
function twindragon(_size, _order, _dir)
{
  root2 = Math.sqrt(2);

  if (_order < 1 || _size < 1) {
    fd(_size);
  } else {
	rt(45 * _dir);
    twindragon(_size/(2*root2), _order-1, _dir);
	lt(90 * _dir);
    twindragon(_size/root2, _order-1, _dir);
	rt(90 * _dir);
    twindragon(_size/(2*root2), _order-1, _dir);
	lt(45 * _dir);
  }
}


//------------------------------------------
function square_sweep(_size, _order, _ang, _dir)
{
  var sideLen = (_size/2)/Math.sin(_ang*conv);
  var topLen = _size - _size/Math.tan(_ang*conv);
//alert("_size is" + _size);
  if (_order < 1 || _size < 1) {
    fd(_size);
  } else {
	lt(_ang * _dir);
    square_sweep(sideLen, _order-1, _ang, -_dir);
	rt(_ang * _dir);
    square_sweep(topLen/2, _order-1, _ang, _dir);
    square_sweep(topLen/2, _order-1, _ang, _dir);
	rt(_ang * _dir);
    square_sweep(sideLen, _order-1, _ang, -_dir);
	lt(_ang * _dir);
  }
}


//------------------------------------------
function tree(_size, _order, _angle, _ratio) {

	fd(_size);
	if (_order > 0 && _size > 1) {
		lt(_angle);
		tree(_size*_ratio, _order-1, _angle, _ratio);
		rt(_angle*2);
		tree(_size*_ratio, _order-1, _angle, _ratio);
		lt(_angle);
	}
	bk(_size);
}


//------------------------------------------
function tree2(_size, _order) {

	fd(_size);
	if (_order > 0 && _size > 1) {
		lt(30);
		tree2(_size/1.5, _order-1);
		rt(60);
		tree2(_size/1.5, _order-1);
		lt(30);
	}
	bk(_size);
}

