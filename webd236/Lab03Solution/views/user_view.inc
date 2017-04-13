%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <label>First Name:</label>
    <div class='value'>{{$user['firstName']}}</div>
    <label>Last Name:</label>
    <div class='value'>{{$user['lastName']}}</div>
    <label>E-mail:</label>
    <div class='value'>{{$user['email']}}</div>
    <label>Password:</label>
    <div class='value'>[[echo str_repeat('*', strlen($user['password'])); ]]</div>
[[ if (isLoggedIn() && $_SESSION['userid'] == $user['id']) : ]]
    <p><a href="@@user/delete/{{$user['id']}}@@">[Delete]</a> <a href="@@user/edit/{{$user['id']}}@@">[Edit]</a></p>
[[ endif; ]]
</div>
[[ if ($questions) : ]]
<h2>Questions by {{$user['firstName']}} {{$user['lastName']}}</h2>
[[ foreach ($questions as $question) : ]]
  %% views/question_view_short.html %%
[[ endforeach; ]]
[[ endif; ]]

%% views/footer.html %%
