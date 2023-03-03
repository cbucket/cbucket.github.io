// main javascript file for creative computing inspired (basic) js/html programs (e.g. animal.html) */
// Author: Ben Grimer 18sep13

function alert2(varname, obj)
{
  alert(varname + "=>" + obj + "<");
}

function TickYesOrNo(pYN) {

  if (pYN == 'Y') {
    response$ = "Y";
  } else if (pYN == 'N') {
    response$ = "N";
  } else alert("TickYesOrNo(): this should never happen !");

  basPrint(response$);
  processResponse();
  inputtbox.focus();
  return false;
}

function TickNSEWUD(pYN) {

//  index = directions.search(pYN);
//  alert("direction index="+index);
  if (-1 == directions.search(pYN)) { alert("TickNSEWUD(): this should never happen !"); }

  response$ = pYN;
  basPrint(response$);
  processResponse();
  inputtbox.focus();
  return false;
}

function checkEnter(tbox)
{
  var characterCode;

  characterCode = event.keyCode; //character code is contained in IE's keyCode property

  if(characterCode == 13) { //if generated character code is equal to ascii 13 (if enter key)
    event.keyCode = 0
    if (0 == tbox.value.length)
    {
      alert('You cannot leave the answer blank !');
    } else {
      response$ = tbox.value.toUpperCase();
//alert2("response$", response$);
      basPrint(response$);
      processResponse();
      tbox.value = "";
      return false;
    }
  }
  else return true;
}

function basPrintSC(_text) // this function simulates the BASIC print command using a textarea
{
  basPrint(_text, "");
}

function basPrint(_text, _sc) // this function simulates the BASIC print command using a textarea
{
  if (_sc != "CLS") {
    if (!_text) _text = "";
    term1.value = term1.value + _text + ((typeof _sc != 'undefined') ? "" : "\n");
    term1.scrollTop = term1.scrollHeight;  // see: http://stackoverflow.com/questions/9170670
                                           //           /how-do-i-set-textarea-scroll-bar-to-bottom-as-a-default
  } else {
    term1.value = "";
  }
}


function basPrint2(_varname, _value) // this function simulates the BASIC print command using a textarea
{
  basPrint(_varname + "->" + _value + "<");
}

// added 19/09/13 - animal now supports loading/saving
// planned to use for bible quiz also
function getXMLReqObj(window) {
  if (window.XMLHttpRequest) { // code for IE7+, Firefox, Chrome, Opera, Safari
    return (new XMLHttpRequest());
  } else { // code for IE6, IE5
    return (new ActiveXObject("Microsoft.XMLHTTP"));
  }
}
