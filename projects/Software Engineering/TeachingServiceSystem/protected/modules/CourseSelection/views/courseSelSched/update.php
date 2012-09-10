<?php
$this->breadcrumbs=array(
	'Course Sel Scheds'=>array('index'),
	$model->ID=>array('view','id'=>$model->ID),
	'Update',
);

$this->menu=array(
	array('label'=>'List CourseSelSched', 'url'=>array('index')),
	array('label'=>'Create CourseSelSched', 'url'=>array('create')),
	array('label'=>'View CourseSelSched', 'url'=>array('view', 'id'=>$model->ID)),
	array('label'=>'Manage CourseSelSched', 'url'=>array('admin')),
);
?>

<h1>Update CourseSelSched <?php echo $model->ID; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>