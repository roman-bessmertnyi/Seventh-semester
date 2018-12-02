import io from 'socket.io-client';


var SOCKET_HOST = window.location.href;

var CLEAR_DISPLAY_VALUE = '\xa0';

var SOCKET_TOAST_CONNECTED = 'SOCKET was connected';
var SOCKET_TOAST_DISCONNECTED = 'SOCKET lost connection';
var COM_TOAST_CONNECTED = 'COM was connected';
var COM_TOAST_DISCONNECTED = 'COM was disconnected';

var socket;
var comStatus, socketStatus;


//Ready function
document.addEventListener('DOMContentLoaded', function () {

    comStatus = document.getElementById("comStatus");
    socketStatus = document.getElementById("socketStatus");

    socket = io.connect(SOCKET_HOST);

    socket.on('connect', () => {
        M.toast({html: SOCKET_TOAST_CONNECTED, classes: 'green'});
        socketStatus.classList.remove("red-dod");
        socketStatus.classList.add("green-dod");
    });

    socket.on('disconnect', () => {
        M.toast({html: SOCKET_TOAST_DISCONNECTED, classes: 'red'});
        onComDisabled();
        socketStatus.classList.remove("green-dod");
        socketStatus.classList.add("red-dod");
        socket = io.connect(SOCKET_HOST);
    });

    socket.on('output', (msg) => {
        let display = document.getElementById('display-text');
        display.textContent = msg;
    });
    socket.on('com_status', (msg) => {
        if (msg === 1 ) {
            onComEnabled();
        }else if (msg === 0) {
            onComDisabled();
        }
    });

    document.getElementsByClassName('keyboard-key').ondragstart = function () {
        return false;
    };
});

function onComEnabled() {
    // M.toast({html: COM_TOAST_CONNECTED, classes: 'green'}); // To show toast with inform message
    comStatus.classList.remove("red-dod");
    comStatus.classList.add("green-dod");
}

function onComDisabled() {
    // M.toast({html: COM_TOAST_DISCONNECTED, classes: 'red'}); // To show toast with inform message
    comStatus.classList.remove("green-dod");
    comStatus.classList.add("red-dod");
}

function display(value) {
    socket.emit('display', value);
};

// Key press event handler
export function pressKey(key) {
    display(key);
    return false;
};

//Key unpress event handler
export function unpressKey(key) {
    display(CLEAR_DISPLAY_VALUE);
    return false;
};