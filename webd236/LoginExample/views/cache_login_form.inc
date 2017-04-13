<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/LoginExample/static/style.css" />
    </head>
    <body>
        <div class="content">
<?php  include_once 'include/util.inc'; ?>
<?php  if (isLoggedIn()) : ?>
    <p class='login'><a href='/LoginExample/logout'>Log out</a></p>
<?php  else : ?>
    <p class='login'><a href='/LoginExample/login'>Log in</a></p>
<?php  endif; ?>

<h1><?php echo($title); ?></h1>
<?php  if (isset($errors)) : ?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : ?>
        <li><?php echo($error); ?></li>
<?php    endforeach; ?>
    </ul>
<?php  endif; ?>
<div class='inputs'>
    <form action="/LoginExample/login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" value="<?php echo(isset($username) ? $username : ''); ?>" />
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" value="<?php echo(isset($password) ? $password : ''); ?>" />
        <input type="submit" value="Login" />
    <form>
</div>
<p><a href="/LoginExample/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2012 Todd Whittaker
        </div>
        </div><!-- content div -->
    </body>
</html>
