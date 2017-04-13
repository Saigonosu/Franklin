%% views/header.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@todo/update@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$todo['id']}}" />
        <label for="description">Description:</label>
        <input type="text" id="description" name="description" value="{{$todo['description']}}" />
        <label for="done">Done?:</label>
        <input type="text" id="done" name="done" value="{{$todo['done']}}" />
        <input type="submit" value="Update" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
