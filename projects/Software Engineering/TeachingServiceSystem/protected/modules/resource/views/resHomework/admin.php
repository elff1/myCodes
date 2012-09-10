<?php
$this->breadcrumbs=array(
	ResourceModule::t('resHomework', 'Homeworks')=>array('index'),
	ResourceModule::t('resHomework', 'Manage'),
);

$cid = null;
if (isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}

$this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List ResHomework'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	//array('label'=>'Create ResHomework', 'url'=>array('create')),
);

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('res-homework-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1>Manage Res Homeworks</h1>

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
	'id'=>'res-homework-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'student_id',
		'score',
		'assignment_id',
		'teachingclass_id',
		'comments',
        'submit_time',
		/*
		'resource_id',
		*/
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
