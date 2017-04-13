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
<div class='display'>
    <label>Description:</label>
    <div class='value'><?php echo($todo['description']); ?></div>
    <label>Done?:</label>
    <div class='value'><?php echo($todo['done'] ? 'yes' : 'no'); ?></div>
</div>
<p><a href="/LoginExample/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2012 Todd Whittaker
        </div>
        </div><!-- content div -->
    </body>
</html>
