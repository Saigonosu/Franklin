<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title);
?></title>
        <link rel="stylesheet" href="/Authentication/static/style.css" />
    </head>
    <body>
        <div class="content">
<?php 
  include_once 'include/util.inc';
  include_once 'include/Authenticator.inc';
  include_once 'models/User.inc';

?>

<ul id="navigation">
<?php  if (isLoggedIn()) : 
?>
  <li class="left">Welcome, <?php echo(User::findById($_SESSION['userid'])->getFullName());
?></li>
  <li class="right"><a href="/Authentication/logout">Log out</a></li>
  <?php  if (Authenticator::instance()->can('admin_page')) : 
?>
    <li class="right"><a href="/Authentication/admin">Admin</a></p>
  <?php  endif; 
?>
  <li class="right"><a href="/Authentication/user/view/<?php echo($_SESSION['userid']);
?>">My profile</a></li>
<?php  else : 
?>
  <li class="right"><a href="/Authentication/login">Log in</a></li>
  <li class="right"><a href="/Authentication/user/register">Register</a></li>
<?php  endif; 
?>
  <li class="right"><a href="/Authentication/index">Home</a></li>
</ul>

<h1><?php echo($title);
?></h1>
<?php  if (isset($errors)) : 
?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : 
?>
        <li><?php echo($error);
?></li>
<?php    endforeach; 
?>
    </ul>
<?php  endif; 
?>
<div class='inputs'>
    <form action="/Authentication/todo/update" method="post">
        <input type="hidden" id="id" name="id" value="<?php echo($todo->getId());
?>" />
        <label for="description">Description:</label>
        <input type="text" id="description" name="description" value="<?php echo($todo->getDescription());
?>" />
        <label for="done">Done?:</label>
        <input type="text" id="done" name="done" value="<?php echo($todo->getDone());
?>" />
        <input type="submit" value="Update" />
    <form>
</div>
<p><a href="/Authentication/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2012 Todd Whittaker
        </div>
<?php 
//debug(print_r($_SESSION, true));
//$inSession = session_id();
//debug($inSession);

?>

        </div><!-- content div -->
    </body>
</html>
