<div class="wide form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'action'=>Yii::app()->createUrl($this->route),
	'method'=>'get',
)); ?>

	<div class="row">
		<?php echo $form->label($model,'course_name'); ?>
		<?php echo $form->textField($model,'course_name'); ?>
	</div>
	
	<div class="row">
		<?php echo $form->label($model,'time'); ?>
		<?php echo $form->dropDownList($model,'time',array(
					'1'=>'1,2jie',
					'2'=>'3,4jie',
					'3'=>'5,6jie',
					'9'=>'7,9jie',)); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton('Search'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- search-form -->