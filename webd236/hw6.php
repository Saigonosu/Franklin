<?php
//Ryan Devlin
//WebD 236
//Prof. Sharkey
//HW 6

function reduce($arr, $func, $start = 0){
  $current = $start;
  for($i=0;$i<count($arr);$i++){
    $next = $arr[$i];
    $current = $func($current, $next);
  }
  return $current;
}

$array = array(10, 5, 3, 5, 1, 2, 5, 7, 4,);
function myMax($current, $new){
  return $current < $new ? $new : $current;
}
function sum($first, $second){
  return $first + $second;
}
function modeMaker(){
  $seen = array();
  return function($current, $new) use (&$seen){
    $seen[$new] += 1;
    return $seen[$current] < $seen[$new] ? $new : $current;
  };
}
$mode = modeMaker();

class Car {
    private $gas = 0;
    private $mpg = 0;
    private $odometer = 0;

  public function __construct($initialGas, $mpg){
    $this->gas = $initialGas;
    $this->mpg = $mpg;
    $this->odometer = 0;
  }

  public function __toString() {
   return 'Car (gas: ' . $this->readFuelGauge() .
      ', miles: ' . $this->readOdometer() . ')';
   }

  public function drive($miles){
    $fuel_available = $this->readFuelGauge();
    $max_drivable_distance = ($fuel_available * $this->mpg);
    if($max_drivable_distance < $miles){
      $this->odometer += $max_drivable_distance;
      $this->gas = 0;
    }
    else {
      $fuel_used = $miles/$this->mpg;
      $this->odometer += $miles;
      $this->gas = $fuel_available - $fuel_used;
    }
  }

  public function addGas($gallons){
    $this->gas += $gallons;
  }

  public function readFuelGauge(){
    return $this->gas;
  }

  public function readOdometer(){
    return $this->odometer;
  }
}
$my_car = new Car(50, 100);

?>
<!DOCTYPE html>
<html>
  <head>
    <title>Homework 6!</title>
  </head>
  <body>
    <p>array is <?php print_r($array); ?></p>
    <p>Function is
    <pre>
      function myMax($current, $new){
        return $current &lt; $new ? $new : $current;
      }
    </pre>
    <p><?php echo reduce($array, 'myMax');?>
    <p>Next function is
    <pre>
      function sum($first, $second){
        return $first + $second;
      }
    </pre>
    <p><?php echo reduce($array, 'sum');?>
    <p>Reduce can take a parameter for a starting value! Let's start each with 100. This wasn't a requirement, I stole it from Ruby :)</p>
    <p><?php echo reduce($array, 'myMax', 100);?>
    <p><?php echo reduce($array, 'sum', 100);?>
    <p>This is supposed to be the mode thingy. I think this is what they want</p>
    <p><?php echo reduce($array, $mode);?>

    <p>My car before driving: <?php echo $my_car; ?></p>
    <?php $my_car->drive(250); ?>
    <p>My car after driving 250 miles: <?php echo $my_car; ?></p>
<?php
$car = new Car(20, 25);
$car -> drive(25);
print($car . '<br />');
$car -> drive(1000);
print($car . '<br />');
$car -> addGas(5);
$car -> drive(10);
print($car . '<br />');
?>
  </body>
</html>
