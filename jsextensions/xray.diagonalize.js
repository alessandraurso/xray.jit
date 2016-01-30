/*
	xray.diagonalize.js by Wesley Smith 7/31/2005
*/

var interpolated = new JitterMatrix();
interpolated.name = "interpolated";
interpolated.interp = 0;
interpolated.adapt = 0;

var diagonal  = new JitterMatrix();
var makediagonal = new JitterObject("jit.expr");
makediagonal.expr = "(in[0]) * (cell[0] == cell[1])";

//setinletassist(-1, describe_in);
//setoutletassist(-1, describe_out);

function jit_matrix(name)
{
	interpolated.setinfo(name);
	interpolated.dim = [interpolated.dim[0], interpolated.dim[0]];
	interpolated.frommatrix(name);
	diagonal.setinfo(interpolated);
	makediagonal.matrixcalc(interpolated, diagonal);

	outlet(0, "jit_matrix", diagonal.name);
}

function describe_in(num)
{
	assist("jit_matrix row vector");
}

function describe_out(num)
{
	assist("jit_matrix")
}