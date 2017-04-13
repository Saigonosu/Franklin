<?php
//Ryan Devlin
//Prof Sharkey
//WebD236
//2-6-16
function removeAllValuesMatching($arr, $value){
  return array_diff($arr, array($value));
}
function removeDuplicates($arr){
  $temp_arr = $arr;
  $element_counts = array_count_values($arr);
  foreach($element_counts as $value => $count){
    if($count > 1){
      $temp_arr = removeAllValuesMatching($temp_arr, $value);
    }
  }
  return $temp_arr;
}
function findSpellings($word, $allWords){
  $word_soundex = soundex($word);
  $soundex_hash = computeSoundexHash($allWords);
  $words_that_you_might_have_meant = array_keys(array_intersect($soundex_hash, array($word_soundex)));

  return $words_that_you_might_have_meant;
}
function computeSoundexHash($arr){
  $temp_array = array();
  foreach($arr as $word){
    $temp_array[$word] = soundex($word);
  }
  return $temp_array;
}
$arr = array (
  'a' => 'one',
  'b' => 'two',
  'c' => 'three',
  'd' => 'two',
  'e' => 'four',
  'f' => 'five',
  'g' => 'three',
  'h' => 'two'
);
$value = 'two';

$misspelled_value = 'for';

$words = findSpellings($misspelled_value, $arr);

?>
<!DOCTYPE html>
<html>
  <head>
    <title>HomeWork 4</title>
  </head>
  <body>
    <p><?php echo print_r(removeAllValuesMatching($arr, $value)); ?></p>
    <p><?php echo print_r(removeDuplicates($arr)); ?></p>
      <?php foreach ($words as $word) :?>
    <p>
      <?php echo "You entered: $misspelled_value<br />Did you mean: $word?";?>
    </p>
      <?php endforeach;?>
  </body>
</html>
