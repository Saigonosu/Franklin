%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%

<div class='inputs'>
    <form action='@@{{$action}}@@' method='post'>
        <label for='firstName'>First name</label>
        <input type='text' id='firstName' name='user[firstName]' value='{{$user->getFirstName()}}'/>
        <label for='lastName'>Last name</label>
        <input type='text' id='lastName' name='user[lastName]' value='{{$user->getLastName()}}'/>
        <label for='email'>E-mail address</label>
        <input type='text' id='email' name='user[email]' value='{{$user->getEmail()}}'/>
        <label for='password'>Password</label>
        <input type='text' id='password' name='user[password]' value='{{$user->getPassword()}}'/>
        <input type='hidden' id='id' name='user[id]' value='{{$user->getId()}}' />
        <input type='submit' value='Save' />
    </form>
</div>
%% views/footer.html %% 