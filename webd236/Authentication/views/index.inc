[[ include_once ('include/Authenticator.inc'); ]]
%% views/header.html %%
<h1>{{$title}}</h1>
[[if (Authenticator::instance() -> can('create_todo')) : ]]
<form action="@@todo/add@@" method="post">
    <label for="description">Description:</label>
    <input type="text" id="description" name="todo[description]" />
    <input type="submit" value="Add" />
</form>
[[ endif; ]]
<h2>Current To Do:</h2>
<ol>
    [[ foreach ($todos as $todo) : ]]
    <li>
        [[ if (Authenticator::instance() -> can('view_todo')) : ]]
        <a href="@@todo/view/{{$todo->getId()}}@@">[View]</a>
        [[ endif; ]]
        [[ if (Authenticator::instance() -> can('edit_todo')) : ]]
        <a href="@@todo/edit/{{$todo->getId()}}@@">[Edit]</a>
        [[ endif; ]]
        [[ if (Authenticator::instance() -> can('delete_todo')) : ]]
        <a href="@@todo/delete/{{$todo->getId()}}@@">[Del]</a>
        [[ endif; ]]
        {{$todo->getDescription()}}
    </li>
    [[ endforeach; ]]
</ol>

<h2>Past To Do:</h2>
<ol>
    [[ foreach ($dones as $todo) : ]]
    <li>
        [[ if (Authenticator::instance() -> can('view_todo')) : ]]
        <a href="@@todo/view/{{$todo->getId()}}@@">[View]</a>
        [[ endif; ]]
        [[ if (Authenticator::instance() -> can('edit_todo')) : ]]
        <a href="@@todo/edit/{{$todo->getId()}}@@">[Edit]</a>
        [[ endif; ]]
        [[ if (Authenticator::instance() -> can('delete_todo')) : ]]
        <a href="@@todo/delete/{{$todo->getId()}}@@">[Del]</a>
        [[ endif; ]]
        {{$todo->getDescription()}}
    </li>
    [[ endforeach; ]]
</ol>

%% views/footer.html %% 