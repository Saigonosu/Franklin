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
<form action='/webd236/Authentication/group/add' method='post'>
    <label for="name">Group name:</label>
    <input type="text" id="name" name="group[name]" />
    <input type="submit" value="Add" />
</form>
<ul>
    <?php  foreach($groups as $group) : ?>
    <li><a href='/webd236/Authentication/group/members/<?php echo($group->getId());?>'>[Members]</a> <a href='/webd236/Authentication/group/permissions/<?php echo($group->getId());?>'>[Permissions]</a> <a href='/webd236/Authentication/group/delete/<?php echo($group->getId());?>'>[Delete]</a> <?php echo($group->getName());?></li> 
    <?php  endforeach; ?> 
</ul>
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
