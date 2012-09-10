<?php

require dirname(__FILE__).'/db.php';
//
// uncomment the following to define a path alias
// Yii::setPathOfAlias('local','path/to/local-folder');

// This is the main Web application configuration. Any writable
// CWebApplication properties can be configured here.
return array(
	'basePath'=>dirname(__FILE__).DIRECTORY_SEPARATOR.'..',
	
	//set language
	//'language'=>'zh_cn',
	'sourceLanguage'=>'en_us',
	
	'name'=>'Teaching Service System',
	
	// preloading 'log' component
	'preload'=>array('log'),

	// autoloading model and component classes
	'import'=>array(
		'application.models.*',
		'application.components.*',
		'application.modules.rights.*', //rbac
		'application.modules.rights.components.*', //rbac
		
		/*---------Red6------Online Test Subsystem  begins--------------*/
		'application.modules.testOnline.models.*',
		'application.modules.testOnline.components.*',
		'application.modules.testOnline.*',
		/*---------Red6------Online Test Subsystem  begins--------------*/
			
        /*---------Red4------Resource Subsystem begins------------------*/
        'application.modules.resource.models.*',
        'application.modules.resource.controllers.*',
        'application.extensions.unique.*',
        /*-------- Red4------Resource Subsystem ends--------------------*/
		'application.extensions.phpass.*', //password encryption
		
		/*---------Red1------Information Management Subsystem  begins--------------*/
		'application.modules.informationManagement.models.*',
		'application.modules.informationManagement.components.*',
		'application.modules.informationManagement.*',
		/*---------Red1------Information Management Subsystem  ends--------------*/
		
	    'application.modules.CourseSelection.models.*',
		
        'application.modules.courseArrangement.models.*',
		
		
		/*------red7-------------- score management subsystem begins--------------*/
		'application.modules.scoreManagement.models.*',
		'application.modules.scoreManagement.components.*',
		'application.modules.scoreManagement.*',
		/*------red7-------------- score management subsystem ends--------------*/
		
	),

	'modules'=>array(
		// uncomment the following to enable the Gii tool
		
		'gii'=>array(
			'class'=>'system.gii.GiiModule',
			'password'=>'123',
		 	// If removed, Gii defaults to localhost only. Edit carefully to taste.
			'ipFilters'=>array('127.0.0.1','::1'),
		),
		
		
		'rights'=>array(
			'superuserName'=>'SystemAdmin',
			
			'userClass'=>'UserAuthentication',
			'userIdColumn'=>'id',
			'userNameColumn'=>'id',
			//'install'=>true,
		),
		'testOnline',//red6
        'resource',
		'courseArrangement',
		'informationManagement',//red1
		'scoreManagement', //red7
		
		'CourseSelection',
		
		
		'comment'=>array(
			'class'=>'ext.comment-module.CommentModule',
			'commentableModels'=>array(
				'post'=>'ResResource',
				),
			'userModelClass'=>'UserAuthentication',
			'userNameAttribute'=>'id',
			'userEmailAttribute'=>'id',
			'onDeleteComment'=>array('ResResourceController', 'onDeleteComment'),
            'onNewComment'=>array('ResResourceController', 'onNewComment'),
		)
	),

	// application components
	'components'=>array(
		'user'=>array(
			'class'=>'RWebUser',//rights
			// enable cookie-based authentication
			'allowAutoLogin'=>true,
		),
		// uncomment the following to enable URLs in path-format
		/*
		'urlManager'=>array(
			'urlFormat'=>'path',
			'rules'=>array(
				'<controller:\w+>/<id:\d+>'=>'<controller>/view',
				'<controller:\w+>/<action:\w+>/<id:\d+>'=>'<controller>/<action>',
				'<controller:\w+>/<action:\w+>'=>'<controller>/<action>',
			),
		),
		*/
		/*
		'db'=>array(
			'connectionString' => 'sqlite:'.dirname(__FILE__).'/../data/testdrive.db',
		),
		*/
		// uncomment the following to use a MySQL database
		
		'db'=>array(
			'connectionString' => $connectionString,
			'emulatePrepare' => $emulatePrepare,
			'username' => $username,
			'password' => $password,
			'charset' => $charset,
		),
		
		'errorHandler'=>array(
			// use 'site/error' action to display errors
            'errorAction'=>'site/error',
        ),
		'log'=>array(
			'class'=>'CLogRouter',
			'routes'=>array(
				array(
					'class'=>'CFileLogRoute',
					'levels'=>'error, warning',
				),
				// uncomment the following to show log messages on web pages
				/*
				array(
					'class'=>'CWebLogRoute',
				),
				*/
				//route for database logging
				array(
					'class'=>'CFileLogRoute',
					'categories'=>'db',
					'logFile'=>'db.log',
				),
			),
		),
		
		'authManager'=>array(
			'class'=>'RDbAuthManager',
			'connectionID'=>'db',
			'defaultRoles'=>array('Guest','Authenticated'), 		
		),
		
		'file'=>array(
        	'class'=>'application.extensions.file.CFile',
    	),
    	
    	'hasher'=>array (
			'class'=>'Phpass',
			'hashPortable'=>false,
			'hashCostLog2'=>10,
		),
		'request'=>array(
            //'enableCsrfValidation'=>true,
        ),
	),

	// application-level parameters that can be accessed
	// using Yii::app()->params['paramName']
	'params'=>array(
		// this is used in contact page
		'adminEmail'=>'zym1010@gmail.com',
		//max file size for batch upload
		'maxBatchCreateFileSize'=>1024*1024*2,//1mb by default
	),
);
