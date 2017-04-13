%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%

<div class='inputs'>
    <form action='@@question/add@@' method='post'>
        <label for='questionTitle'>Title</label>
        <input type='text' id='questionTitle' name='questionTitle' value='{{$questionTitle}}'/>
        <label for='content'>Content</label>
        <textarea id='content' name='content' rows='20' cols='60'>{{$content}}</textarea>
        <label for='tags'>Tags</label>
        <input type='text' id='tags' name='tags' value='{{$tags}}'/>
        <input type='submit' value='Submit Question' />
    </form>
</div>
%% views/footer.html %%
