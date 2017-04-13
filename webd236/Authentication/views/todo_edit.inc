%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@todo/update@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$todo->getId()}}" />
        <label for="description">Description:</label>
        <input type="text" id="description" name="description" value="{{$todo->getDescription()}}" />
        <label for="done">Done?:</label>
        <input type="text" id="done" name="done" value="{{$todo->getDone()}}" />
        <input type="submit" value="Update" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
