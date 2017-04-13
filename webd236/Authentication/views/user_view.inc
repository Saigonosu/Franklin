[[ include_once("include/Authenticator.inc"); ]]
%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <label>First Name:</label>
    <div class='value'>{{$user->getFirstName()}}</div>
    <label>Last Name:</label>
    <div class='value'>{{$user->getLastName()}}</div>
    <label>E-mail:</label>
    <div class='value'>{{$user->getEmail()}}</div>
    <label>Password:</label>
    <div class='value'>[[echo str_repeat('*', strlen($user->getPassword())); ]]</div>
[[ if (isLoggedIn() && ($_SESSION['userid'] == $user->getId()) || Authenticator::instance()->can('edit_user')): ]]
    <p><a href="@@user/delete/{{$user->getId()}}@@">[Delete]</a> <a href="@@user/edit/{{$user->getId()}}@@">[Edit]</a></p>
[[ endif; ]]
</div>

%% views/footer.html %%
