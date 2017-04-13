<!DOCTYPE html>
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/webd236/mvc-template/static/style.css" />
    </head>
    <body>
        <div class="content">

<h1><?php echo($title); ?></h1>
<h2>List of Current Records</h2>
<table>
  <tr>
    <th>ACTION</td>
    <th>Field 1</th>
    <th>Field 2</th>
    <th>Field 3</th>
  </tr>
  <?php  foreach ($records as $record) : ?>
  <tr>
    <td>
      <a href="/webd236/mvc-template/sample/view/<?php echo($record['id']); ?>">[View]</a>
      ||
      <a href="/webd236/mvc-template/sample/edit/<?php echo($record['id']); ?>">[Edit]</a>
      ||
      <a href="/webd236/mvc-template/sample/delete/<?php echo($record['id']); ?>">[Del]</a>
    </td>
    <td><?php echo($record['field1']); ?></td>
    <td><?php echo($record['field2']); ?></td>
    <td><?php echo($record['field3']); ?></td>
  </tr>
  <?php  endforeach; ?>
</table>

<hr />

<form action="/webd236/mvc-template/sample/add" method="post">
<fieldset>
    <label for="field1">Field 1:</label>
    <input type="text" id="field1" name="field1" /><br />
    <label for="field2">Field 2:</label>
    <input type="text" id="field2" name="field2" /><br />
    <label for="field3">Field 3:</label>
    <input type="text" id="field3" name="field3" /><br />
    <input type="submit" value="Add New Record" />
</fieldset>
</form>

            <div class="footer">
                Copyright &copy; 2014 Scott Sharkey
            </div>
        </div><!-- content div -->
    </body>
</html>

