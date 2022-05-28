<?php
//echo '<B>saveanimal.php (c) Ben Grimer 2013</B>.  Current PHP version: ' . phpversion() . '<br>';

$content = $_POST['editor']; 
$file = $_POST['savefile']; 

//echo "content>" . $content . "< <br>";
$pieces = explode(",", $content);
//echo "MM" . $pieces[0] . "mm" . "<br>";
//echo "MM" . $pieces[1] . "mm" . "<br>";

$Saved_File = fopen($file, 'w'); 
for ($i=0; $i<sizeof($pieces); $i++) {
  fprintf($Saved_File, "%s\n", $pieces[$i]);
}
//fwrite($Saved_File, $content); 
fclose($Saved_File); 

$response = "Saved: ".$_POST['savefile']." (size: ".strlen($_POST['editor'])." modified: ".date("d/m/Y H:i:s", filemtime($file)).")";
echo $response;
?>