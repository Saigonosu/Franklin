%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@login@@" method="post">
        <label for="email">Email address:</label>
        <input type="text" id="email" name="email" value="{{$email}}" />
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" value="{{$password}}" />
        <input type="submit" value="Login" />
    <form>
</div>
%% views/footer.html %%
