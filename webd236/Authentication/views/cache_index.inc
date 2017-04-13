<?php  include_once ('include/Authenticator.inc'); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title);?></title>
        <link rel="stylesheet" href="/webd236/Authentication/static/style.css" />
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
  <li class="right"><a href="/webd236/Authentication/logout">Log out</a></li>
  <?php  if (Authenticator::instance()->can('admin_page')) : ?>
    <li class="right"><a href="/webd236/Authentication/admin">Admin</a></p>
  <?php  endif; ?>
  <li class="right"><a href="/webd236/Authentication/user/view/<?php echo($_SESSION['userid']);?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/webd236/Authentication/login">Log in</a></li>
  <li class="right"><a href="/webd236/Authentication/user/register">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/webd236/Authentication/index">Home</a></li>
</ul>

<h1><?php echo($title);?></h1>
<?php if (Authenticator::instance() -> can('create_todo')) : ?>
<form action="/webd236/Authentication/todo/add" method="post">
    <label for="description">Description:</label>
    <input type="text" id="description" name="todo[description]" />
    <input type="submit" value="Add" />
</form>
<?php  endif; ?>
<h2>Current To Do:</h2>
<ol>
    <?php  foreach ($todos as $todo) : ?>
    <li>
        <?php  if (Authenticator::instance() -> can('view_todo')) : ?>
        <a href="/webd236/Authentication/todo/view/<?php echo($todo->getId());?>">[View]</a>
        <?php  endif; ?>
        <?php  if (Authenticator::instance() -> can('edit_todo')) : ?>
        <a href="/webd236/Authentication/todo/edit/<?php echo($todo->getId());?>">[Edit]</a>
        <?php  endif; ?>
        <?php  if (Authenticator::instance() -> can('delete_todo')) : ?>
        <a href="/webd236/Authentication/todo/delete/<?php echo($todo->getId());?>">[Del]</a>
        <?php  endif; ?>
        <?php echo($todo->getDescription());?>
    </li>
    <?php  endforeach; ?>
</ol>

<h2>Past To Do:</h2>
<ol>
    <?php  foreach ($dones as $todo) : ?>
    <li>
        <?php  if (Authenticator::instance() -> can('view_todo')) : ?>
        <a href="/webd236/Authentication/todo/view/<?php echo($todo->getId());?>">[View]</a>
        <?php  endif; ?>
        <?php  if (Authenticator::instance() -> can('edit_todo')) : ?>
        <a href="/webd236/Authentication/todo/edit/<?php echo($todo->getId());?>">[Edit]</a>
        <?php  endif; ?>
        <?php  if (Authenticator::instance() -> can('delete_todo')) : ?>
        <a href="/webd236/Authentication/todo/delete/<?php echo($todo->getId());?>">[Del]</a>
        <?php  endif; ?>
        <?php echo($todo->getDescription());?>
    </li>
    <?php  endforeach; ?>
</ol>

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