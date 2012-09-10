<?php
$this->breadcrumbs=array(
	'Online Test Subsystem'=>array('/testOnline'),
	'Course List'=>array('default/listCourses'),
	AccountComponent::getSelected_course_name()=>array('paperBank/'),
	AccountComponent::getSelected_paper_id()=>array('paperBank/view', 'id'=>AccountComponent::getSelected_paper_id()),
	'List',
);

$this->menu=array(
	array('label'=>'Create Paper', 'url'=>array('create')),
	array('label'=>'Manage Paper', 'url'=>array('admin')),
);
?>

<h1>List Problems</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
