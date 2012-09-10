<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	'Manage',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'View Classroom'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Create Classroom'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Manage Classroom'), 'url'=>array('admin')),
	
);

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('classroom-basic-info-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1>Manage Classroom Basic Infos</h1>

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
	'id'=>'classroom-basic-info-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'room_number',
		'location',
		'campus',
		'type',
		'capacity',
		/*
		'college',
		*/
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
