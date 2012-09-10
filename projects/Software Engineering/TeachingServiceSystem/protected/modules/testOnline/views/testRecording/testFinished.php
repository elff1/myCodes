<?php
$this->breadcrumbs = array (
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'TestFinished' 
);

$this->menu = array (
		array (
				'label' => 'Back to other papers',
				'url' => array (
						'paperBank/' 
				) 
		)); 
?>

<div class="flash-notice">
	<?php echo Yii::app()->user->getFlash("finish_reason")?>
</div>

<!-- form -->