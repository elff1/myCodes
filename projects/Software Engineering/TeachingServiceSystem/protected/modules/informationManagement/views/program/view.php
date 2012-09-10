<?php
$this->breadcrumbs=array(
	'Programs'=>array('index'),
	$model->name,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List Program', 'url'=>array('index')),
	array('label'=>'Create Program', 'url'=>array('create')),
	array('label'=>'Update Program', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete Program', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage Program', 'url'=>array('admin')),
	array('label'=>'Add a course to this program', 'url'=>array('programDetail/create','pid'=>$model->id)),
);
?>

<h1>View Program #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'name',
		
		array(
			'name'=>'department_id',
			'value'=>$model->department===null?null:$model->department->name,
		),
		
		
		array(
			'name'=>'length',
			'value'=>$model->length===null?null:$model->lengthOptions[$model->length],
		),
		
		'grade',
		array(
			'name'=>'introduction',//ntext so that new line can be shown.
			'visible'=>true,
			'type'=>'raw',
			'value'=>CHtml::textArea('intro',$model->introduction,array('readonly'=>'readonly')),
		),
	),
)); ?>

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'dataProvider'=>$courseDataProvider,
	'columns'=>array(
        'course_id',          // display the 'title' attribute
        'required',
        'course.name',
        'program.name',
    ),
)); ?>
