<?php
$this->breadcrumbs=array(
	ResourceModule::t('resResource','Res Resources')=>array('index','uid'=>Yii::app()->user->id),
	ResourceModule::t('resResource','Manage'),
);

$this->menu=array(
	array('label'=>ResourceModule::t('resResource','List ResResource'), 'url'=>array('index', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
);

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('res-resource-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1>Manage Res Resources</h1>

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
	'id'=>'res-resource-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'path',
		'display_name',
		'uploader_id',
		'download_count',
		'resource_type',
		/*
		'description',
		'upload_time',
		*/
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
