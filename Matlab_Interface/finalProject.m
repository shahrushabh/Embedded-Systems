function varargout = finalProject(varargin)
% FINALPROJECT MATLAB code for finalProject.fig
%      FINALPROJECT, by itself, creates a new FINALPROJECT or raises the existing
%      singleton*.
%
%      H = FINALPROJECT returns the handle to a new FINALPROJECT or the handle to
%      the existing singleton*.
%
%      FINALPROJECT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in FINALPROJECT.M with the given input arguments.
%
%      FINALPROJECT('Property','Value',...) creates a new FINALPROJECT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before finalProject_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to finalProject_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help finalProject

% Last Modified by GUIDE v2.5 01-May-2015 13:10:12

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @finalProject_OpeningFcn, ...
                   'gui_OutputFcn',  @finalProject_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before finalProject is made visible.
function finalProject_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to finalProject (see VARARGIN)

% Choose default command line output for finalProject
handles.output = handles;

% Update handles structure
guidata(hObject, handles);
% UIWAIT makes finalProject wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% Global Variables storing the path history. pathTaken and pathNum is
% number of commnads sent to robot.
global pathTaken;
global pathNum;
pathTaken = cell(1,100);
pathNum = 1;

% Global variable for serial communication between matlab and robot.
global s;
s = instrfind('Type', 'serial', 'Port', 'COM4', 'Tag', '');


% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(s)
    s = serial('COM4');
else
    fclose(s);
    s = s(1);
end

% Attempt to open connection to iRobot.
fopen(s);

% Configure the specification of serial communication.
% BaudRate of 57600
% Num of stop bits 2
% Data Terminator 13
% Reading mode 'Continuous'
set(s, 'BaudRate', 57600);
set(s, 'StopBits', 2.0);
set(s, 'Terminator',13);
s.ReadAsyncMode = 'continuous';


% --- Outputs from this function are returned to the command line.
function varargout = finalProject_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in ScanButton.
function ScanButton_Callback(hObject, eventdata, handles)
% hObject    handle to ScanButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%Global initialization.
global s;
% Update Status Bar.
set(handles.data,'String','Scanning...');
input = zeros(2,180);
fwrite(s,'s');
x = ones(1,180);
y = ones(1,180);
a = 1;
% Receive data from robot sensor and manipulate them to appropriate units.
while (a <= 180)
    [input(1,a), input(2,a)] = strread(fgetl(s));
    input(1,a) = (input(1,a) * (pi / 180));
    x(1,a) = input(1,a);
    y(1,a) = input(2,a);
    a = a + 1;
end
% Plot the angles and distance received to a polar graph.
polar(x,y,'r');
drawnow;
% Update Linear Width, Angle, and Distance to most current values.
inputwidth = ones(1,5);
a = 1;
while (a < 6)
    inputwidth(1,a) = strread(fgetl(s));
    a = a + 1;
end
set(handles.Width,'String',inputwidth(1,:));
a = 1;
while (a < 6)
    inputwidth(1,a) = strread(fgetl(s));
    a = a + 1;
end
set(handles.dis,'String',inputwidth(1,:));
a = 1;
while (a < 6)
    inputwidth(1,a) = strread(fgetl(s));
    a = a + 1;
end
set(handles.ang,'String',inputwidth(1,:));

% Updates Status bar.
set(handles.data,'String','Waiting for next command..');

% --- Executes on button press in ForwardButton.
function ForwardButton_Callback(hObject, eventdata, handles)
% hObject    handle to ForwardButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
global pathTaken;
global pathNum;
%  d: temporary variable stores amount specified in the editable text box.
d = int16(str2num(get(handles.getAmount,'String')));
a = idivide(d,10);
b = d - (a * 10);
% Sends command to the robot with the amount specified for moving forward.
fwrite(s,'f');
fwrite(s,a);
fwrite(s,b);

% Check for any interruption occured during the movement.
interruption = 'a';
while(strcmp(interruption,'a') == 1)
    interruption = fgets(s);
        if strcmp(interruption,'NONE') == 1
            % Show the movement was successful without any interruption.
            % Update the path history panel as well.
            set(handles.data,'String','SUCCESSFUL!');
            pathTaken(1,pathNum) = strcat({'Moved Forward '},int2str(d));
            set(handles.path,'String',pathTaken(1,1:pathNum));
            pathNum = pathNum + 1;
            break
        elseif strcmp(interruption,'B L') == 1
            %Show LEFT BUMPER HIT.
            set(handles.data,'String','BUMPER TO THE LEFT');
            break
        elseif strcmp(interruption,'B R') == 1
            %Show RIGHT BUMPER HIT.
            set(handles.data,'String','BUMPER TO THE RIGHT');
            break
        elseif strcmp(interruption,'F L CL') == 1
            %Show CLIFF TO THE LEFT WATCH OUT
            set(handles.data,'String','CLIFF TO THE FRONT LEFT. CAREFUL!');
            break
        elseif strcmp(interruption,'F R CL') == 1
            %Show CLIFF TO THE LEFT WATCH OUT
            set(handles.data,'String','CLIFF TO THE FRONT RIGHT. CAREFUL!');
            break
        elseif strcmp(interruption,'L CL') == 1
            %Show CLIFF TO THE LEFT WATCH OUT
            set(handles.data,'String','CLIFF TO THE LEFT. CAREFUL!');
            break
        elseif strcmp(interruption,'R CL') == 1
            %Show CLIFF TO THE LEFT WATCH OUT
            set(handles.data,'String','CLIFF TO THE RIGHT. CAREFUL!');
            break
        elseif strcmp(interruption,'F L BLACK') == 1
            %Show Goal Reached at Front Left
            set(handles.data,'String','GOAL REACHED AT FRONT LEFT. BLACK');
            break
        elseif strcmp(interruption,'F R BLACK') == 1
            %Show Goal Reached at Front Right
            set(handles.data,'String','GOAL REACHED AT FRONT RIGHT. BLACK');
            break
        elseif strcmp(interruption,'L BLACK') == 1
            %Show Goal Reached at Left
            set(handles.data,'String','GOAL REACHED AT LEFT. BLACK');
            break
        elseif strcmp(interruption,'R BLACK') == 1
            %Show Goal Reached at Front Right
            set(handles.data,'String','GOAL REACHED AT RIGHT. BLACK');
            break
        elseif strcmp(interruption,'F W') == 1
            %Show WHITE LINE IN FRONT
            set(handles.data,'String','WHITE LINE IN FRONT');
            break
        elseif strcmp(interruption,'L W') == 1
            %Show WHITE LINE TO THE LEFT
            set(handles.data,'String','WHITE LINE IN LEFT');
            break
        elseif strcmp(interruption,'R W') == 1
            %Show WHITE LINE TO THE RIGHT
            set(handles.data,'String','WHITE LINE IN RIGHT');
            break
        end
end


% --- Executes on button press in BackwardButton.
function BackwardButton_Callback(hObject, eventdata, handles)
% hObject    handle to BackwardButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
global pathTaken;
global pathNum;
%  d: temporary variable stores amount specified in the editable text box.
d = int16(str2num(get(handles.getAmount,'String')));
a = idivide(d,10);
b = d - (a * 10);
% Sends command to the robot with the amount specified for moving backwards.
fwrite(s,'b');
fwrite(s,a);
fwrite(s,b);

% Update the path history panel as well.
pathTaken(1,pathNum) = strcat({'Moved Backward '},int2str(d));
set(handles.path,'String',pathTaken(1,1:pathNum));
pathNum = pathNum + 1;


% --- Executes on button press in LeftButton.
function LeftButton_Callback(hObject, eventdata, handles)
% hObject    handle to LeftButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
global pathTaken;
global pathNum;
%  d: temporary variable stores amount specified in the editable text box.
d = int16(str2num(get(handles.getAmount,'String')));
a = idivide(d,10);
b = d - (a * 10);
% Sends command to the robot with the amount specified for turning left.
fwrite(s,'l');
fwrite(s,a);
fwrite(s,b);

% Update the path history panel as well.
pathTaken(1,pathNum) = strcat({'Turned Left '},int2str(d));
set(handles.path,'String',pathTaken(1,1:pathNum));
pathNum = pathNum + 1;


% --- Executes on button press in RightButton.
function RightButton_Callback(hObject, eventdata, handles)
% hObject    handle to RightButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
global pathTaken;
global pathNum;
%  d: temporary variable stores amount specified in the editable text box.
d = int16(str2num(get(handles.getAmount,'String')));
a = idivide(d,10);
b = d - (a * 10);
% Sends command to the robot with the amount specified for turning right.
fwrite(s,'r');
fwrite(s,a);
fwrite(s,b);

% Update the path history panel as well.
pathTaken(1,pathNum) = strcat({'Turned Right '},int2str(d));
set(handles.path,'String',pathTaken(1,1:pathNum));
pathNum = pathNum + 1;


function getAmount_Callback(hObject, eventdata, handles)
% hObject    handle to getAmount (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of getAmount as text
%        str2double(get(hObject,'String')) returns contents of getAmount as a double


% --- Executes during object creation, after setting all properties.
function getAmount_CreateFcn(hObject, eventdata, handles)
% hObject    handle to getAmount (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function Reconnect_ClickedCallback(hObject, eventdata, handles)
% hObject    handle to Reconnect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
s = instrfind('Type', 'serial', 'Port', 'COM4', 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.

% Attempt to reconnect robot.
fopen(s);

% Configure the new connection with appropriate specification.
set(s, 'BaudRate', 57600);
set(s, 'StopBits', 2.0);
set(s, 'Terminator',13);
s.ReadAsyncMode = 'continuous';


% --------------------------------------------------------------------
function Disconnect_ClickedCallback(hObject, eventdata, handles)
% hObject    handle to Disconnect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
% Disconnect and end the communication.
fclose(s);
delete(s);


% --------------------------------------------------------------------
function info_ClickedCallback(hObject, eventdata, handles)
% hObject    handle to info (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
% Get the technical specification about current connection.
get(s);


% --- Executes on button press in park.
function park_Callback(hObject, eventdata, handles)
% hObject    handle to park (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
% We have reached to our goal so park teh robot.
% Command essentially moves 10cm and ignores all interruptions.
fwrite(s,'p');


% --- Executes on button press in play.
function play_Callback(hObject, eventdata, handles)
% hObject    handle to play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
% Celebration for a successful run.
fwrite(s,'m');


% --- Executes on slider movement.
function scroll_Callback(hObject, eventdata, handles)
% hObject    handle to scroll (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global pathTaken;
global pathNum;
% Update the history visible based on the position of scroller.
position = get(handles.scroll,'Value');
set(handles.path,'String',pathTaken(1,(position*pathNum): pathNum));

% --- Executes during object creation, after setting all properties.
function scroll_CreateFcn(hObject, eventdata, handles)
% hObject    handle to scroll (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
