<?php
//Ryan Devlin
//Prof Sharkey
//WebD236
//2-2-16
function print_date() {
  $date = new DateTime('', new DateTimeZone('EST'));
  echo $date->format('l, M d, Y, g:i:s A, T');
}

function isLetter($ch){
  $ascii = ord($ch);
  return isCapitalLetter($ascii) || isLowerCaseLetter($ascii);
}
function isCapitalLetter($ascii){
  return in_array($ascii, range(ord('A'),ord('Z')));
}
function isLowerCaseLetter($ascii){
  return in_array($ascii, range(ord('a'),ord('z')));
}
function myReverse($string){
  $letters = str_split($string);
  $letters_reversed = array_reverse($letters);
  $reversed_string = implode('', $letters_reversed);
  return $reversed_string;
}
function removePunctuation($string){
  $letters = str_split($string);
  $temp_array = [];
  foreach ($letters as $letter){
    if (isLetter($letter)){
      array_push($letter, $temp_array);
    }
  }
  return implode('', $temp_array);
}
function removeWhiteSpace($string){
  return str_replace( ' ', '', $string);
}
function isPalindrome($string){
  $string = removeWhiteSpace($string);
  $string = removePunctuation($string);
  return $string === myReverse($string);
}
function replaceConsonant($ch){
  if (in_array(strtolower($ch), array('b','f','p','v'))){
    return  "1";
  }
  elseif (in_array(strtolower($ch), array('c','g','j','k','q','s','x','z'))){
    return  "2";
  }
  elseif (in_array(strtolower($ch), array('d','t'))){
    return  "3";
  }
  elseif (in_array(strtolower($ch), array('l'))){
    return  "4";
  }
  elseif (in_array(strtolower($ch), array('m','n'))){
    return  "5";
  }
  elseif (in_array(strtolower($ch), array('r'))){
    return  "6";
  }
  else {
    return $ch;
  }
}
function mySoundex($name){
  //save first letter of name
  $first_letter = $name[0];

  //Removes w and h from name except first letter
  if (in_array(array('w','h'), $first_letter)){
    $name = str_replace('w', '', $name);
    $name = str_replace('h', '', $name);
    $name = $first_letter.$name;
  }
  else {
    $name = str_replace('w', '', $name);
    $name = str_replace('h', '', $name);
  }

  //replaces consonants with numbers from algorithm
  foreach (str_split($name) as $index=>$letter){
    $name = str_replace($letter, replaceConsonant($letter), $name);
  }

  //de-duplicate adjacent repeating values
  $name = preg_replace('/(.)\1/i','$1', $name);

  //replace vowels except for first letter
  $name = $name[0].preg_replace('/([aeiouy]*)/i','', substr($name,1,strlen($name)-1));

  //If first letter is a number, replace it with first letter from earlier
  if (!isLetter($name[0])){
    $name[0] = $first_letter;
  }

  //if < 3 numbers, pad with zeros, if > 3 take only first 3 digits. Results in 4 character string
  if (strlen($name) < 4){
    $name = str_pad($name, 4, '0');
  }
  elseif (strlen($name) > 4){
    $name = substr($name, 0, 4);
  }

  //return final string;
  return $name;
}

$names = array("Euler", "Ellery", "Gauss", "Ghosh", "Hilbert", "Heilbronn", "Knuth", "Kant", "Leida",
  "Ladd", "Lukasiewicz", "Lissajous");
?>
<!DOCTYPE html>
<html>
  <head>
    <title>HomeWork 4</title>
  </head>
  <body>
    <p><?php print_date() ?></p>
    <p><?php echo isLetter('1') ? 'True' : 'False' ?></p>
    <p><?php echo isLetter('m') ? 'True' : 'False' ?></p>
    <p><?php echo 'String is Ryan, reversed is ' . myReverse('Ryan') ?></p>
    <p><?php echo isPalindrome('A man, a plan, a canal, Panama!') ? 'True' : 'False' ?></p>
    <p><?php echo mySoundex("Ryan"); ?></p>

      <?php foreach ($names as $name) :?>
    <p>
      <?php echo "$name has Soundex value of: ".mySoundex($name).'<br>';?>
      <?php echo "PHP says $name has Soundex value of: ".soundex($name);?>
    </p>
      <?php endforeach;?>

  </body>
</html>
