clear;
 clc;
 
  % choose a video file
 [filename, pathname] = uigetfile('*.avi', 'choose a video file', 'video.avi', 'Multiselect', 'on');
 
 fprintf('filename = %s \npathname = %s \n\n', filename, pathname);
 
  if ischar(filename)
     
     fprintf('choose file success.\n\n');
     
     video = mmreader([pathname filename]);
     len = video.NumberOfFrames; % get length of the video
     
     fprintf('length of video : %d \n\n', len);
     
     dir=strcat(pathname,strrep(filename,'.avi',''),'\pic');
     mkdir(dir); % create folder for saving picture
     fn=strrep(filename,'.avi',''); 
     
     for k = 1 : len - 1
         frame = rgb2gray(read(video, k));
         imwrite(frame,strcat(dir,'\',fn,'-avi-000',int2str(k),'.bmp'),'bmp'); 
     end
     
 end