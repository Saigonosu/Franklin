%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Recent Questions</h2>
[[ if ($questions) : ]]
[[ foreach ($questions as $question) : ]]
  %% views/question_view_short.html %%
[[ endforeach; ]]
[[ endif; ]]
[[ if (isLoggedIn()) : ]]
<p><a href="@@question/add@@">Add a question</a></p>
[[ endif; ]]
%% views/footer.html %%
