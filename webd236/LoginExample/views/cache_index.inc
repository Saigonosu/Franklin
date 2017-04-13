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
<?php if (isLoggedIn()) : ?>
<form action="/LoginExample/todo/add" method="post">
    <label for="description">Description:</label>
    <input type="text" id="description" name="description" />
    <input type="submit" value="Add" />
</form>
<?php  endif; ?>
<h2>Current To Do:</h2>
<ol>
    <?php  foreach ($todos as $todo) : ?>
    <li>
        <?php if (isLoggedIn()) : ?>
        <a href="/LoginExample/todo/view/<?php echo($todo['id']); ?>">[View]</a> <a href="/LoginExample/todo/edit/<?php echo($todo['id']); ?>">[Edit]</a> <a href="/LoginExample/todo/delete/<?php echo($todo['id']); ?>">[Del]</a>
        <?php  endif; ?>
        <?php echo($todo['description']); ?>
    </li>
    <?php  endforeach; ?>
</ol>

<h2>Past To Do:</h2>
<ol>
    <?php  foreach ($dones as $todo) : ?>
    <li>
        <?php if (isLoggedIn()) : ?>
        <a href="/LoginExample/todo/view/<?php echo($todo['id']); ?>">[View]</a> <a href="/LoginExample/todo/edit/<?php echo($todo['id']); ?>">[Edit]</a> <a href="/LoginExample/todo/delete/<?php echo($todo['id']); ?>">[Del]</a>
        <?php  endif; ?>
        <?php echo($todo['description']); ?>
    </li>
    <?php  endforeach; ?>
</ol>

        <div class="footer">
            Copyright &copy; 2012 Todd Whittaker
        </div>
        </div><!-- content div -->
    </body>
</html> 