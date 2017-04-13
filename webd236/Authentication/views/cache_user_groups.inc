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
<h2>Member of</h2>
<ul>
    <?php  foreach($memberOf as $group) : 
?>
    <li><a href='/Authentication/group/remove/<?php echo($group->getId());
?>/<?php echo($user->getId());
?>/'>[Leave]</a> <?php echo($group->getName());
?></li> 
    <?php  endforeach; 
?> 
</ul>
<h2>Available groups</h2>
<ul>
    <?php  foreach($notMemberOf as $group) : 
?>
    <li><a href='/Authentication/group/include/<?php echo($group->getId());
?>/<?php echo($user->getId());
?>/'>[Join]</a> <?php echo($group->getName());
?></li> 
    <?php  endforeach; 
?> 
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
