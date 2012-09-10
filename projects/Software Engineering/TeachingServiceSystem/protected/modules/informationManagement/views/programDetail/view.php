<?php
$this->breadcrumbs=array(
	'Program Details'=>array('index'),
	$model->id,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List ProgramDetail', 'url'=>array('index')),
	array('label'=>'Create ProgramDetail', 'url'=>array('create')),
	array('label'=>'Update ProgramDetail', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete ProgramDetail', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage ProgramDetail', 'url'=>array('admin')),
);
?>

<h1>View ProgramDetail #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'program_id',
		'course_id',
		'type',
		'required',
		'recommended_year',
		'recommended_term',
	),
)); ?>
