%% views/header.html %%
<h1>{{$title}}</h1>
[[
    include_once 'models/user.inc';
    $questioner = findUserById($question['userId']);
    $name = $questioner['firstName'] . ' ' . $questioner['lastName'];
]]
<p>Posted {{$question['postedOn']}} by <a href='@@user/view/{{$question['userId']}}@@'>{{$name}}</a></p>
[[ if (isset($question['tags']) && $question['tags'] != '') : ]]
<p>Filed under: {{$question['tags']}}</p>
[[ endif; ]]
<p>[[ echo (nl2br($question['content'])); ]]</p>

[[ if (isLoggedIn() && $_SESSION['userid'] == $question['userId']) : ]]
<p><a href="@@question/delete/{{$question['id']}}@@">[Delete]</a> <a href="@@question/edit/{{$question['id']}}@@">[Edit]</a></p>
[[ endif; ]]

%% views/footer.html %%
