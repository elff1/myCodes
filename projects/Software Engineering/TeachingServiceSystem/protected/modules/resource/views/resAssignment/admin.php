<?php
$this->breadcrumbs=array(
	ResourceModule::t('resAssignment', 'Assignments')=>array('index'),
	ResourceModule::t('resAssignment', 'Manage'),
);

$cid = null;
if(isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}

// show different menu
$this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'List Assignment'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Create Assignment'), 'url'=>array('create', 'teachingclass_id'=>$cid)),
);

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('res-assignment-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

    <h1><?php echo ResourceModule::t('resAssignment', 'Manage Assignment'); ?></h1>

<p>
You may optionally enter a comparison operator (<b>&lt;</b>, <b>&lt;=</b>, <b>&gt;</b>, <b>&gt;=</b>, <b>&lt;&gt;</b>
or <b>=</b>) at the beginning of each of your search values to specify how the comparison should be done.
</p>

<?php echo CHtml::link('Advanced Search','#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'res-assignment-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'teachingclass_id',
		'resource_id',
		'dead_line',
		'is_published',
		'teacher_id',
		/*
		'requirement',
		*/
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
