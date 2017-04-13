%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%

<div class='inputs'>
    <form action='@@question/edit@@' method='post'>
        <label for='questionTitle'>Title</label>
        <input type='text' id='questionTitle' name='question[title]' value='{{$question["title"]}}'/>
        <label for='content'>Content</label>
        <textarea id='content' name='question[content]' rows='20' cols='60'>{{$question["content"]}}</textarea>
        <label for='tags'>Tags</label>
        <input type='text' id='tags' name='question[tags]' value='{{$question["tags"]}}'/>
        <input type='hidden' id='id' name='question[id]' value='{{$question["id"]}}' />
        <input type='submit' value='Save' />
    </form>
</div>
%% views/footer.html %%
