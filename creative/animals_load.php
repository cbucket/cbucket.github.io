<?php
/* This php file get the saved animal list for the program animal.html
 * (see the html calling file for more details)
 * Ben Grimer 18/09/13
 */

  $animal_ary = array();
  $file = fopen("animal.sav", "r") or exit("Unable to open file!");  // animal.sav contains the question/answer array
  while(!feof($file)) {

    $line = trim(fgets($file));
    $animal_ary[] = $line;
  } // end while
  fclose($file);
  $final = implode( ",", $animal_ary );
  echo $final;  
?>