<?php
// the breadcrumbs list
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('index'),
		'Generate Paper',
);

// the menu list
$this->menu=array(
	array('label'=>'List PaperBank', 'url'=>array('index')),
	array('label'=>'Manage PaperBank', 'url'=>array('admin')),
);
?>

<!-- the title -->
<h1>Create Paper</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model));
 ?>