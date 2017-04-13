<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title);?></title>
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
<?php  if (isLoggedIn()) : ?>
  <li class="left">Welcome, <?php echo(User::findById($_SESSION['userid'])->getFullName());?></li>
  <li class="right"><a href="/Authentication/logout">Log out</a></li>
  <?php  if (Authenticator::instance()->can('admin_page')) : ?>
    <li class="right"><a href="/Authentication/admin">Admin</a></p>
  <?php  endif; ?>
  <li class="right"><a href="/Authentication/user/view/<?php echo($_SESSION['userid']);?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/Authentication/login">Log in</a></li>
  <li class="right"><a href="/Authentication/user/register">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/Authentication/index">Home</a></li>
</ul>

<h1><?php echo($title);?></h1>

<?php  if (isset($errors)) : ?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : ?>
        <li><?php echo($error);?></li>
<?php    endforeach; ?>
    </ul>
<?php  endif; ?>

<div class='inputs'>
    <form action='/Authentication/<?php echo($action);?>' method='post'>
        <label for='firstName'>First name</label>
        <input type='text' id='firstName' name='user[firstName]' value='<?php echo($user->getFirstName());?>'/>
        <label for='lastName'>Last name</label>
        <input type='text' id='lastName' name='user[lastName]' value='<?php echo($user->getLastName());?>'/>
        <label for='email'>E-mail address</label>
        <input type='text' id='email' name='user[email]' value='<?php echo($user->getEmail());?>'/>
        <label for='password'>Password</label>
        <input type='text' id='password' name='user[password]' value='<?php echo($user->getPassword());?>'/>
        <input type='hidden' id='id' name='user[id]' value='<?php echo($user->getId());?>' />
        <input type='submit' value='Save' />
    </form>
</div>
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