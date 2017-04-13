<?php

// CUSTOMIZED version to determine why people are having issues with this on Windows 10.

// Dump an array in a pretty format...
function dumpArray($elements) {
    $result = "<ol>\n";
    foreach ($elements as $key => $value) {
        if (is_array($value)) {
            $result .= "<li>Key <b>$key</b> is an array
                containing:\n" . dumpArray($value) . "</li>";
        } else {
            $value = nl2br(htmlspecialchars($value));
            $result .= "<li>Key <b>$key</b> has value [<b>$value</b>]</li>\n";
        }
    }
    return $result . "</ol>\n";
}

// Dump a variable in a nice debug <div>...
function debug($header, $something) {
    echo "<h1>$header</h1>\n";
    echo "<div class='debug'>\n";
    print_r($something);
    echo "\n</div>\n";
}

function routeUrl() {
    $method = $_SERVER['REQUEST_METHOD'];
    debug('Method', $method);
    $requestURI = explode('/', $_SERVER['REQUEST_URI']);
    debug('Original RequestURI', dumpArray($requestURI));
    $scriptName = explode('/', $_SERVER['SCRIPT_NAME']);
    debug('ScriptName', $scriptName);

    for ($i = 0; $i < sizeof($scriptName); $i++) {
        if ($requestURI[$i] == $scriptName[$i]) {
            unset($requestURI[$i]);
        }
    }
    debug('Modified RequestURI', dumpArray($requestURI))

    $command = array_values($requestURI);
    debug('command', $command);
    $controller = 'controllers/' . $command[0] . '.inc';
    debug('controller', $controller);
    $func = strtolower($method) . '_' . (isset($command[1]) ? $command[1] : 'index');
    debug('function', $func);
    $params = array_slice($command, 2);
    debug('params', dumpArray($params));
}

routeUrl();
