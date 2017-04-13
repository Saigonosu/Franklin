%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <label>Description:</label>
    <div class='value'>{{$todo['description']}}</div>
    <label>Done?:</label>
    <div class='value'>{{$todo['done'] ? 'yes' : 'no'}}</div>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
