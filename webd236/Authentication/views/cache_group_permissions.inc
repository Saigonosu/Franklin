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
<h2>Granted permissions</h2>
<ul>
    <?php  foreach($permissions as $permission) : ?>
    <li><a href='/Authentication/group/revoke/<?php echo($group->getId());?>/<?php echo($permission->getId());?>/'>[Revoke]</a> <?php echo($permission->getName());?></li> 
    <?php  endforeach; ?> 
</ul>
<h2>Available permissions</h2>
<ul>
    <?php  foreach($nonpermissions as $permission) : ?>
    <li><a href='/Authentication/group/grant/<?php echo($group->getId());?>/<?php echo($permission->getId());?>/'>[Grant]</a> <?php echo($permission->getName());?></li> 
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
