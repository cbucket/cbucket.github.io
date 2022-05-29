// polygons.js (20/02/11)

//irrelevant due to shape:

function triangle(_x) { polygon(_x, 3); }

function square(_x)   { polygon(_x, 4); }

function pentagon(_x) { polygon(_x, 5); }

function hexagon(_x)  { polygon(_x, 6); }

function octogon(_x)  { polygon(_x, 8); }

function polygon(_size, _numSides)
{
  var i;
  for (i=0; i<_numSides; i++) {
    fd(_size);
    rt(360/_numSides);
  }
}

// demo shapes function:
function shapes() {

	lt(30);
	triangle(30);
	square(40);
  pentagon(50);
  hexagon(60);
  octogon(70);

}

// draws a star with n points
// only works for odd numbers > 4
function star(_size, _numPoints)
{
  for (i=0; i<_numPoints; i++) {
    fd(_size);
    rt(360*2/_numPoints);
  }

}

